// ignore_for_file: require_trailing_commas
// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import 'package:camera/camera.dart';
import 'package:firebase_ml_vision/firebase_ml_vision.dart';
import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';

import 'detector_painters.dart';
import 'scanner_utils.dart';

class CameraPreviewScanner extends StatefulWidget {
  const CameraPreviewScanner({Key? key}) : super(key: key);

  @override
  State<StatefulWidget> createState() => _CameraPreviewScannerState();
}

class _CameraPreviewScannerState extends State<CameraPreviewScanner> {
  dynamic _scanResults;
  CameraController? _camera;
  Detector _currentDetector = Detector.text;
  bool _isDetecting = false;
  CameraLensDirection _direction = CameraLensDirection.back;

  final BarcodeDetector _barcodeDetector =
      FirebaseVision.instance.barcodeDetector();
  final FaceDetector _faceDetector = FirebaseVision.instance.faceDetector();
  final ImageLabeler _imageLabeler = FirebaseVision.instance.imageLabeler();
  final ImageLabeler _cloudImageLabeler =
      FirebaseVision.instance.cloudImageLabeler();
  final TextRecognizer _recognizer = FirebaseVision.instance.textRecognizer();
  final TextRecognizer _cloudRecognizer =
      FirebaseVision.instance.cloudTextRecognizer();
  final DocumentTextRecognizer _cloudDocumentRecognizer =
      FirebaseVision.instance.cloudDocumentTextRecognizer();

  @override
  void initState() {
    super.initState();
    _initializeCamera();
  }

  Future<void> _initializeCamera() async {
    final CameraDescription description =
        await ScannerUtils.getCamera(_direction);

    _camera = CameraController(
      description,
      defaultTargetPlatform == TargetPlatform.iOS
          ? ResolutionPreset.low
          : ResolutionPreset.medium,
      enableAudio: false,
    );
    await _camera!.initialize();

    await _camera!.startImageStream((CameraImage image) {
      if (_isDetecting) return;

      _isDetecting = true;

      ScannerUtils.detect(
        image: image,
        detectInImage: _getDetectionMethod()!,
        imageRotation: description.sensorOrientation,
      ).then(
        (dynamic results) {
          if (!mounted) return;
          setState(() {
            _scanResults = results;
          });
        },
      ).whenComplete(() => _isDetecting = false);
    });
  }

  Future<dynamic> Function(FirebaseVisionImage image)? _getDetectionMethod() {
    switch (_currentDetector) {
      case Detector.text:
        return _recognizer.processImage;
      case Detector.cloudText:
        return _cloudRecognizer.processImage;
      case Detector.cloudDocumentText:
        return _cloudDocumentRecognizer.processImage;
      case Detector.barcode:
        return _barcodeDetector.detectInImage;
      case Detector.label:
        return _imageLabeler.processImage;
      case Detector.cloudLabel:
        return _cloudImageLabeler.processImage;
      case Detector.face:
        return _faceDetector.processImage;
    }
  }

  Widget _buildResults() {
    const Text noResultsText = Text('No results!');

    if (_scanResults == null ||
        _camera == null ||
        !_camera!.value.isInitialized) {
      return noResultsText;
    }

    CustomPainter painter;

    final Size imageSize = Size(
      _camera!.value.previewSize!.height,
      _camera!.value.previewSize!.width,
    );

    switch (_currentDetector) {
      case Detector.barcode:
        if (_scanResults is! List<Barcode>) return noResultsText;
        painter = BarcodeDetectorPainter(imageSize, _scanResults);
        break;
      case Detector.face:
        if (_scanResults is! List<Face>) return noResultsText;
        painter = FaceDetectorPainter(imageSize, _scanResults);
        break;
      case Detector.label:
        if (_scanResults is! List<ImageLabel>) return noResultsText;
        painter = LabelDetectorPainter(imageSize, _scanResults);
        break;
      case Detector.cloudLabel:
        if (_scanResults is! List<ImageLabel>) return noResultsText;
        painter = LabelDetectorPainter(imageSize, _scanResults);
        break;
      default:
        assert(_currentDetector == Detector.text ||
            _currentDetector == Detector.cloudText);
        if (_scanResults is! VisionText) return noResultsText;
        painter = TextDetectorPainter(imageSize, _scanResults);
    }

    return CustomPaint(
      painter: painter,
    );
  }

  Widget _buildImage() {
    return Container(
      constraints: const BoxConstraints.expand(),
      child: _camera == null
          ? const Center(
              child: Text(
                'Initializing Camera...',
                style: TextStyle(
                  color: Colors.green,
                  fontSize: 30,
                ),
              ),
            )
          : Stack(
              fit: StackFit.expand,
              children: <Widget>[
                CameraPreview(_camera!),
                _buildResults(),
              ],
            ),
    );
  }

  Future<void> _toggleCameraDirection() async {
    if (_direction == CameraLensDirection.back) {
      _direction = CameraLensDirection.front;
    } else {
      _direction = CameraLensDirection.back;
    }

    await _camera!.stopImageStream();
    await _camera!.dispose();

    setState(() {
      _camera = null;
    });

    await _initializeCamera();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('ML Vision Example'),
        actions: <Widget>[
          PopupMenuButton<Detector>(
            onSelected: (Detector result) {
              _currentDetector = result;
            },
            itemBuilder: (BuildContext context) => <PopupMenuEntry<Detector>>[
              const PopupMenuItem<Detector>(
                value: Detector.barcode,
                child: Text('Detect Barcode'),
              ),
              const PopupMenuItem<Detector>(
                value: Detector.face,
                child: Text('Detect Face'),
              ),
              const PopupMenuItem<Detector>(
                value: Detector.label,
                child: Text('Detect Label'),
              ),
              const PopupMenuItem<Detector>(
                value: Detector.cloudLabel,
                child: Text('Detect Cloud Label'),
              ),
              const PopupMenuItem<Detector>(
                value: Detector.text,
                child: Text('Detect Text'),
              ),
              const PopupMenuItem<Detector>(
                value: Detector.cloudText,
                child: Text('Detect Cloud Text'),
              ),
              const PopupMenuItem<Detector>(
                value: Detector.cloudDocumentText,
                child: Text('Detect Document Text'),
              ),
            ],
          ),
        ],
      ),
      body: _buildImage(),
      floatingActionButton: FloatingActionButton(
        onPressed: _toggleCameraDirection,
        child: _direction == CameraLensDirection.back
            ? const Icon(Icons.camera_front)
            : const Icon(Icons.camera_rear),
      ),
    );
  }

  @override
  void dispose() {
    _camera!.dispose().then((_) {
      _barcodeDetector.close();
      _faceDetector.close();
      _imageLabeler.close();
      _cloudImageLabeler.close();
      _recognizer.close();
      _cloudRecognizer.close();
    });

    super.dispose();
  }
}
