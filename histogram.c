#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int width;
    int height;
    int maxPixelValue;
    int* pixelValues; // Pointer instead of array
} PGMImage;

// Function to read PGM file
PGMImage* readPGM(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    PGMImage* image = (PGMImage*)malloc(sizeof(PGMImage));
    if (!image) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "P2\n%d %d\n%d\n", &image->width, &image->height, &image->maxPixelValue);

    image->pixelValues = (int*)malloc(image->width * image->height * sizeof(int));
    if (!image->pixelValues) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < image->width * image->height; ++i) {
        fscanf(file, "%d", image->pixelValues + i);
    }

    fclose(file);
    return image;
}

// Function to write PGM file
void writePGM(const char* filename, PGMImage* image) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "P2\n%d %d\n%d\n", image->width, image->height, image->maxPixelValue);

    for (int i = 0; i < image->width * image->height; ++i) {
        fprintf(file, "%d ", *(image->pixelValues + i));
    }

    fclose(file);
}

// Function to perform histogram equalization
void histogramEqualization(PGMImage* inputImage, PGMImage* outputImage) {
    // Compute the histogram
    int* histogram = (int*)calloc(inputImage->maxPixelValue + 1, sizeof(int));

    for (int i = 0; i < inputImage->width * inputImage->height; ++i) {
        histogram[*(inputImage->pixelValues + i)]++;
    }

    // Calculate the cumulative histogram
    int* cumulativeHist = (int*)malloc((inputImage->maxPixelValue + 1) * sizeof(int));
    cumulativeHist[0] = histogram[0];

    for (int i = 1; i <= inputImage->maxPixelValue; ++i) {
        cumulativeHist[i] = cumulativeHist[i - 1] + histogram[i];
    }

    // Image Mapping
    for (int i = 0; i < inputImage->width * inputImage->height; ++i) {
        *(outputImage->pixelValues + i) = (cumulativeHist[*(inputImage->pixelValues + i)] * inputImage->maxPixelValue) / (inputImage->width * inputImage->height);
    }

    // Free memory
    free(histogram);
    free(cumulativeHist);
}

int main() {
    // Read input image
    PGMImage* inputImage = readPGM("Rain_Tree.pgm");

    // Create output image
    PGMImage* outputImage = (PGMImage*)malloc(sizeof(PGMImage));
    outputImage->width = inputImage->width;
    outputImage->height = inputImage->height;
    outputImage->maxPixelValue = inputImage->maxPixelValue;
    outputImage->pixelValues = (int*)malloc(outputImage->width * outputImage->height * sizeof(int));

    // Perform histogram equalization
    histogramEqualization(inputImage, outputImage);

    // Write output image to text PGM file
    writePGM("output_text.pgm", outputImage);

    // Write output image to binary PGM file
    FILE* binaryFile = fopen("output_binary.pgm", "wb");
    if (!binaryFile) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(binaryFile, "P5\n%d %d\n%d\n", outputImage->width, outputImage->height, outputImage->maxPixelValue);
    fwrite(outputImage->pixelValues, sizeof(unsigned char), outputImage->width * outputImage->height, binaryFile);
    fclose(binaryFile);

    // Free memory
    free(inputImage->pixelValues);
    free(inputImage);
    free(outputImage->pixelValues);
    free(outputImage);

    return 0;
}
