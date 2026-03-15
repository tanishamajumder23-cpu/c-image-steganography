# 🖼️ C Image Steganography using LSB

A simple C program that demonstrates **image steganography** by hiding secret text inside a **BMP image** using **Least Significant Bit (LSB) manipulation**.

---

# 📌 Overview

This project hides a secret message inside an image by modifying the **last bit of each pixel byte**.

Since only **1 bit out of 8 bits** is changed, the image looks almost identical to the original.

Example message hidden in the image:

HELLO

---

# ⚙️ How It Works

The program works like a **pipeline** where data moves through steps:

Secret Message
↓
Convert characters → Binary
↓
Read input BMP image
↓
Extract image bytes
↓
Replace Least Significant Bit (LSB)
↓
Write modified bytes
↓
Generate output image with hidden message

---

# 🧠 Core Logic

The entire steganography process happens in this line:

```c
imageByte = (imageByte & 0xFE) | messageBit;
```

This performs two operations:

1. **Clear the last bit of the pixel**
2. **Insert the secret message bit**

---

# 🔎 Step 1 — Extracting a Bit from the Message

Code used:

```c
(secretMessage[messageIndex] >> (7 - bitIndex)) & 1
```

Example character:

```
H = 01001000
```

If we want the **first bit**, we shift the number until that bit reaches the rightmost position.

```
01001000 >> 7
00000000
```

Now we apply the mask:

```
& 00000001
```

Result:

```
0
```

So the extracted **messageBit = 0**

The mask `& 1` removes all other bits and keeps only the **last bit**.

---

# ✏️ Step 2 — Clearing the Pixel Bit (The Eraser)

Before inserting our secret bit, we must erase the last bit of the pixel.

Mask used:

```
0xFE = 11111110
```

Example pixel:

```
11111111
```

Apply AND:

```
11111111
11111110
--------
11111110
```

Now the last bit becomes **0**.

This creates an empty slot for the secret bit.

---

# 🔗 Step 3 — Inserting the Secret Bit (The Glue)

Now we insert the message bit using OR.

If message bit = 1

```
11111110
00000001
--------
11111111
```

If message bit = 0

```
11111110
00000000
--------
11111110
```

So the pixel's last bit becomes exactly the **message bit**.

---

# 🔄 Handling Each Character

Each character contains **8 bits**.

The program uses counters:

```c
bitIndex++;

if(bitIndex == 8)
{
    bitIndex = 0;
    messageIndex++;
}
```

Meaning:

* Hide **8 bits of one character**
* Then move to the next character

Example message:

```
H → E → L → L → O
```

Each letter requires **8 pixels**.

---

# 📂 Copying the Remaining Image

After hiding the message, the rest of the image must remain unchanged.

```c
while ((imageByte = fgetc(inputImage)) != EOF)
{
    fputc(imageByte, outputImage);
}
```

This loop simply **copies the remaining bytes** from the input image to the output image.

Without this step, the image file would become corrupted.

---

# 📁 Project Structure

```
c-image-steganography
│
├── main.c
├── input.bmp
├── output.bmp
└── README.md
```

---

# ▶️ Example Execution

Input:

```
Secret Message: HELLO
Carrier Image: input.bmp
```

Output:

```
output.bmp
```

The output image looks visually identical to the input image, but the message is hidden inside its pixel data.

---

# 🧩 Concepts Demonstrated

* Least Significant Bit (LSB) Steganography
* Binary Data Manipulation
* Bitwise Operations in C
* File Handling in C
* Basic Information Hiding Techniques

---

# 🚀 Possible Improvements

Future enhancements could include:

* Implementing **message decoding**
* Supporting **longer messages**
* Adding **encryption before embedding**
* Supporting **PNG images**
* Adding **steganalysis resistance**

---

# 👩‍💻 Author

Tanisha Majumder
