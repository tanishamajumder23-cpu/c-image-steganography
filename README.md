# c-image-steganography
A C program demonstrating image steganography by embedding secret messages inside BMP images using bit-level manipulation.

**Image Steganography using LSB in C**

Overview

This project demonstrates Image Steganography using the Least Significant Bit (LSB) technique implemented in the C programming language.

The program hides a secret text message inside a BMP image by modifying the least significant bit of image pixel bytes. Since only the last bit of each byte is changed, the visual appearance of the image remains almost identical to the original.

This project was implemented using Code::Blocks on Windows to understand:

Binary data representation

Bitwise operations

Image file structure

Secure data hiding techniques

Main Concept (Data Flow)

The program works like a pipeline where information flows through stages.

Secret Message
      ↓
Convert Characters to Binary
      ↓
Read Input BMP Image
      ↓
Extract Image Bytes
      ↓
Replace Least Significant Bit (LSB)
      ↓
Write Modified Bytes
      ↓
Generate Output Image with Hidden Message
Core Bit Manipulation Logic

The key line of the program is:

imageByte = (imageByte & 0xFE) | messageBit;

This line performs two operations:

Clear the last bit of the pixel

Insert the secret message bit

Step 1 — Extracting a Bit from the Secret Message

The following code extracts one bit from a character:

(secretMessage[messageIndex] >> (7 - bitIndex)) & 1

Example using character H

ASCII of H

H = 01001000

If we want the first bit, we shift the number right until that bit reaches the far right.

Example shift:

01001000 >> 7

Result:

00000000

Now we apply the mask:

& 1

Mask:

00000001

The mask removes all other bits and keeps only the last bit.

Final extracted bit:

0

So the extracted messageBit = 0

Step 2 — Clearing the Pixel's Last Bit (The Eraser)

Before inserting our bit, we must erase the pixel's last bit.

The mask used is:

0xFE

Binary of 0xFE

11111110

Example pixel:

11111111  (255)

Apply AND:

11111111
11111110
--------
11111110

Result:

11111110

The last bit becomes 0.

This creates an empty slot where we can place our secret bit.

Step 3 — Gluing the Message Bit

Now we insert the secret bit using OR.

Example if message bit = 1

11111110
00000001
--------
11111111

Example if message bit = 0

11111110
00000000
--------
11111110

This ensures the pixel's last bit exactly matches the message bit.

Final Operation

The complete operation:

imageByte = (imageByte & 0xFE) | messageBit;

Meaning:

Clear the last bit of the pixel

Insert the secret bit

Handling Each Bit of the Message

Each character has 8 bits.

The code uses counters:

bitIndex++
if(bitIndex == 8)
{
    bitIndex = 0
    messageIndex++
}

This means:

Hide 8 bits of one character

Then move to the next character

Example:

H → E → L → L → O

Each letter takes 8 pixels.

Copying the Remaining Image

After the message is hidden, the rest of the image must remain unchanged.

while ((imageByte = fgetc(inputImage)) != EOF)
{
    fputc(imageByte, outputImage);
}

This loop simply copies the remaining bytes from the original image to the output image.

Without this step, the output image would be incomplete.

Project Structure
c-image-steganography
│
├── main.c
├── input.bmp
├── output.bmp
└── README.md
Example Execution

Input:

Secret Message: HELLO
Carrier Image: input.bmp

Output:

output.bmp

The output image looks almost identical to the input image, but the message is hidden in the pixel data.

Key Concepts Demonstrated

Least Significant Bit (LSB) Steganography

Binary Manipulation

Bitwise Operations in C

File Handling in C

Basic Data Security Techniques

Future Improvements

Possible improvements:

Add message decoding functionality

Support larger messages

Combine steganography with encryption

Support additional formats such as PNG

Implement steganalysis resistance

Author

Tanisha Majumder

This project demonstrates Image Steganography using the Least Significant Bit (LSB) technique implemented in the C programming language.

The program hides a secret text message inside a BMP image by modifying the least significant bit of image pixel bytes. Since only the last bit of each byte is changed, the visual appearance of the image remains almost identical to the original.

This project was implemented using Code::Blocks on Windows to understand:

Binary data representation

Bitwise operations

Image file structure

Secure data hiding techniques

Main Concept (Data Flow)

The program works like a pipeline where information flows through stages.

Secret Message
      ↓
Convert Characters to Binary
      ↓
Read Input BMP Image
      ↓
Extract Image Bytes
      ↓
Replace Least Significant Bit (LSB)
      ↓
Write Modified Bytes
      ↓
Generate Output Image with Hidden Message
Core Bit Manipulation Logic

The key line of the program is:

imageByte = (imageByte & 0xFE) | messageBit;

This line performs two operations:

Clear the last bit of the pixel

Insert the secret message bit

Step 1 — Extracting a Bit from the Secret Message

The following code extracts one bit from a character:

(secretMessage[messageIndex] >> (7 - bitIndex)) & 1

Example using character H

ASCII of H

H = 01001000

If we want the first bit, we shift the number right until that bit reaches the far right.

Example shift:

01001000 >> 7

Result:

00000000

Now we apply the mask:

& 1

Mask:

00000001

The mask removes all other bits and keeps only the last bit.

Final extracted bit:

0

So the extracted messageBit = 0

Step 2 — Clearing the Pixel's Last Bit (The Eraser)

Before inserting our bit, we must erase the pixel's last bit.

The mask used is:

0xFE

Binary of 0xFE

11111110

Example pixel:

11111111  (255)

Apply AND:

11111111
11111110
--------
11111110

Result:

11111110

The last bit becomes 0.

This creates an empty slot where we can place our secret bit.

Step 3 — Gluing the Message Bit

Now we insert the secret bit using OR.

Example if message bit = 1

11111110
00000001
--------
11111111

Example if message bit = 0

11111110
00000000
--------
11111110

This ensures the pixel's last bit exactly matches the message bit.

Final Operation

The complete operation:

imageByte = (imageByte & 0xFE) | messageBit;

Meaning:

Clear the last bit of the pixel

Insert the secret bit

Handling Each Bit of the Message

Each character has 8 bits.

The code uses counters:

bitIndex++
if(bitIndex == 8)
{
    bitIndex = 0
    messageIndex++
}

This means:

Hide 8 bits of one character

Then move to the next character

Example:

H → E → L → L → O

Each letter takes 8 pixels.

Copying the Remaining Image

After the message is hidden, the rest of the image must remain unchanged.

while ((imageByte = fgetc(inputImage)) != EOF)
{
    fputc(imageByte, outputImage);
}

This loop simply copies the remaining bytes from the original image to the output image.

Without this step, the output image would be incomplete.

Project Structure
c-image-steganography
│
├── main.c
├── input.bmp
├── output.bmp
└── README.md
Example Execution

Input:

Secret Message: HELLO
Carrier Image: input.bmp

Output:

output.bmp

The output image looks almost identical to the input image, but the message is hidden in the pixel data.

Key Concepts Demonstrated

Least Significant Bit (LSB) Steganography

Binary Manipulation

Bitwise Operations in C

File Handling in C

Basic Data Security Techniques

Future Improvements

Possible improvements:

Add message decoding functionality

Support larger messages

Combine steganography with encryption

Support additional formats such as PNG

Implement steganalysis resistance

Author

Tanisha Majumder
