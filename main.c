#include <stdio.h>

int main()
{
    FILE *inputImage;
    FILE *outputImage;

    // Message to hide
    char secretMessage[] = "control over information defines security";
    int messageIndex = 0;
    int bitIndex = 0;

    // IMPORTANT: use paths that WORK in Code::Blocks
    inputImage = fopen("bin/Debug/input.bmp", "rb");
    outputImage = fopen("bin/Debug/output.bmp", "wb");
    if (inputImage == NULL || outputImage == NULL)
    {
        printf("Error opening image files.\n");
        return 1;
    }

    int imageByte;
    int headerBytes = 0;

    // STEP 1: Copy first 100 bytes safely (image header area)
    while (headerBytes < 100 && (imageByte = fgetc(inputImage)) != EOF)
    {
        fputc(imageByte, outputImage);
        headerBytes++;
    }

   // STEP 2: Hide message bits
    while (secretMessage[messageIndex] != '\0' &&
           (imageByte = fgetc(inputImage)) != EOF)
    {
        int messageBit =
            (secretMessage[messageIndex] >> (7 - bitIndex)) & 1;

        // Replace last bit of image byte
        imageByte = (imageByte & 0xFE) | messageBit;

        fputc(imageByte, outputImage);

        bitIndex++;

        if (bitIndex == 8)
        {
            bitIndex = 0;
            messageIndex++;
        }
    }

    // STEP 3: Copy remaining image bytes unchanged
    while ((imageByte = fgetc(inputImage)) != EOF)
    {
        fputc(imageByte, outputImage);
    }

    fclose(inputImage);
    fclose(outputImage);
    printf("Message hidden successfully in output.bmp\n");
    return 0;
}
