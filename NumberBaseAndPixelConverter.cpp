//
// Created by light on 9/6/2026.
//

#include <algorithm>
#include <bitset>
#include <cctype>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

struct Pixel {
    int red;
    int green;
    int blue;
};

int digitValue(char character) {
    if (character >= '0' && character <= '9') {
        return character - '0';
    }

    character = static_cast<char>(
        toupper(static_cast<unsigned char>(character))
    );

    if (character >= 'A' && character <= 'F') {
        return character - 'A' + 10;
    }

    return -1;
}

uint32_t parseUnsigned(const string& number, int base) {
    if (number.empty()) {
        throw invalid_argument("The number cannot be empty.");
    }

    uint64_t value = 0;

    for (char character : number) {
        int digit = digitValue(character);

        if (digit < 0 || digit >= base) {
            throw invalid_argument(
                "The number contains an invalid digit for that base."
            );
        }

        value = value * base + static_cast<unsigned int>(digit);

        if (value > numeric_limits<uint32_t>::max()) {
            throw out_of_range(
                "The number is larger than a 32-bit unsigned integer."
            );
        }
    }

    return static_cast<uint32_t>(value);
}

string convertToBase(uint32_t value, int base) {
    const string digits = "0123456789ABCDEF";

    if (value == 0) {
        return "0";
    }

    string result;

    while (value > 0) {
        result.push_back(digits[value % base]);
        value /= base;
    }

    reverse(result.begin(), result.end());
    return result;
}

void asciiToDecimal() {
    string input;

    cout << "Enter one character: ";
    getline(cin, input);

    if (input.length() != 1) {
        cout << "Please enter exactly one character.\n";
        return;
    }

    unsigned char character =
        static_cast<unsigned char>(input[0]);

    cout << "Character: " << input[0] << '\n';
    cout << "Decimal ASCII value: "
         << static_cast<int>(character) << '\n';
}

void numberBaseConverter() {
    int sourceBase;
    string number;

    cout << "Enter the source base (2, 8, 10, or 16): ";
    cin >> sourceBase;

    cout << "Enter the number: ";
    cin >> number;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (sourceBase != 2 &&
        sourceBase != 8 &&
        sourceBase != 10 &&
        sourceBase != 16) {
        cout << "That base is not supported.\n";
        return;
    }

    try {
        uint32_t decimalValue = parseUnsigned(number, sourceBase);

        cout << "\nBinary:      "
             << convertToBase(decimalValue, 2) << '\n';

        cout << "Decimal:     "
             << decimalValue << '\n';

        cout << "Octal:       "
             << convertToBase(decimalValue, 8) << '\n';

        cout << "Hexadecimal: "
             << convertToBase(decimalValue, 16) << '\n';
    }
    catch (const exception& error) {
        cout << "Error: " << error.what() << '\n';
    }
}

void readImagePixels() {
    string filename;

    cout << "Enter the PPM filename to read: ";
    getline(cin, filename);

    ifstream inputFile(filename);

    if (!inputFile) {
        cout << "The file could not be opened.\n";
        return;
    }

    string format;
    int width;
    int height;
    int maximumColorValue;

    inputFile >> format;
    inputFile >> width >> height;
    inputFile >> maximumColorValue;

    if (!inputFile ||
        format != "P3" ||
        width <= 0 ||
        height <= 0 ||
        maximumColorValue != 255) {
        cout << "The program requires a valid P3 PPM image.\n";
        return;
    }

    cout << "Image size: "
         << width << " x " << height << '\n';

    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            Pixel pixel{};

            inputFile >> pixel.red;
            inputFile >> pixel.green;
            inputFile >> pixel.blue;

            if (!inputFile) {
                cout << "The file ended before all pixels were read.\n";
                return;
            }

            cout << "Pixel (" << row << ", " << column << "): ("
                 << pixel.red << ", "
                 << pixel.green << ", "
                 << pixel.blue << ")\n";
        }
    }
}

void createImageFromPixels() {
    string filename;
    int width;
    int height;

    cout << "Enter the output filename (example: image.ppm): ";
    getline(cin, filename);

    cout << "Enter the width and height: ";
    cin >> width >> height;

    if (!cin || width <= 0 || height <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Width and height must be positive integers.\n";
        return;
    }

    vector<Pixel> pixels;
    pixels.reserve(static_cast<size_t>(width) * height);

    cout << "Enter each pixel as red green blue.\n";
    cout << "Each value must be between 0 and 255.\n";

    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            Pixel pixel{};

            cout << "Pixel (" << row << ", "
                 << column << "): ";

            cin >> pixel.red;
            cin >> pixel.green;
            cin >> pixel.blue;

            bool invalidPixel =
                !cin ||
                pixel.red < 0 ||
                pixel.red > 255 ||
                pixel.green < 0 ||
                pixel.green > 255 ||
                pixel.blue < 0 ||
                pixel.blue > 255;

            if (invalidPixel) {
                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n'
                );

                cout << "Invalid pixel. The image was not created.\n";
                return;
            }

            pixels.push_back(pixel);
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    ofstream outputFile(filename);

    if (!outputFile) {
        cout << "The output file could not be created.\n";
        return;
    }

    outputFile << "P3\n";
    outputFile << width << ' ' << height << '\n';
    outputFile << "255\n";

    for (const Pixel& pixel : pixels) {
        outputFile << pixel.red << ' '
                   << pixel.green << ' '
                   << pixel.blue << '\n';
    }

    cout << "Image created successfully: "
         << filename << '\n';
}

void runBoundaryTests() {
    cout << "\n32-bit boundary tests\n\n";

    cout << "Zero in binary: "
         << convertToBase(0, 2) << '\n';

    cout << "Largest unsigned 32-bit value: "
         << numeric_limits<uint32_t>::max() << '\n';

    cout << "Largest unsigned value in hexadecimal: "
         << convertToBase(
                numeric_limits<uint32_t>::max(),
                16
            )
         << '\n';

    int32_t negativeNumber = -42;

    uint32_t sameBitsAsUnsigned =
        static_cast<uint32_t>(negativeNumber);

    cout << "-42 as 32-bit two's complement: "
         << bitset<32>(sameBitsAsUnsigned) << '\n';

    cout << "The same bits interpreted as unsigned: "
         << sameBitsAsUnsigned << '\n';
}

int main() {
    int choice;

    do {
        cout << "\n========================================\n";
        cout << " Number Base and Pixel Converter\n";
        cout << "========================================\n";
        cout << "1. Convert ASCII character to decimal\n";
        cout << "2. Convert between number bases\n";
        cout << "3. Read an image and print pixel values\n";
        cout << "4. Create an image from pixel values\n";
        cout << "5. Run boundary tests\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid menu input.\n";
            return 1;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                asciiToDecimal();
                break;

            case 2:
                numberBaseConverter();
                break;

            case 3:
                readImagePixels();
                break;

            case 4:
                createImageFromPixels();
                break;

            case 5:
                runBoundaryTests();
                break;

            case 0:
                cout << "Program ended.\n";
                break;

            default:
                cout << "Please select a number from 0 through 5.\n";
        }

    } while (choice != 0);

    return 0;
}