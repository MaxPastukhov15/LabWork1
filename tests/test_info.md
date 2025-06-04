# BMP Editor Testing

## Core Tests

### BMP Reading/Writing
- `BMPReadInvalidFile`: Tests handling of non-existent files
- `BMPSaveFile`: Verifies correct file saving
- `BMPSetDimensions`: Tests image dimension setting

### Rotation Tests
- `RotateClockwise`: Tests clockwise rotation
- `RotateCounterClockwise`: Tests counter-clockwise rotation
- `DoubleRotationIdentity`: Verifies rotation identity (round-trip)

### Gaussian Filter Tests
- `GaussianFilterSmallKernel`: Tests small kernel filtering
- `GaussianFilterLargeSigma`: Tests filtering with large sigma value

### Integration Tests
- `RotateThenFilter`: Combined rotation and filtering
- `FilterThenRotateThenSave`: Complex operation with saving

## Testing Features
- Uses temporary `test.bmp` file (3x3 pixels)
- Test files are cleaned up after execution (`TearDown`)
- Verifies both operation correctness and image dimension preservation
