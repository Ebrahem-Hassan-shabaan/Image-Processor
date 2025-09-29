#include <complex>
#include <iostream>
#include <vector>
using namespace std;
#include "Image_Class.h"

int mainMenu() {
    //Done by Ebrahem Hassan
    string menu[10] = {
        "Load New Image", "Grayscale Filter","Black and White filter","Invert Image", "Merge Images","Flip Image","Rotate Image",
        "Resize Image", "Save Image", "Exit"
    };
    int choice;
    cout << "\nPlease select an option:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << i + 1 << ". " << menu[i] << endl;
    }
    cout << "Enter choice: ";
    cin >> choice;
    return choice;
}

Image loadANewImage() {
    //Done by Ebrahem hassan
    cout << "Please enter the filename of the image to load (e.g., photo.jpg): ";
    string filename;
    cin >> filename;
    Image i;
    try {
        i.loadNewImage(filename);
    } catch (const invalid_argument &e) {
        cerr << "Error: Could not load the image. Please check the following:\n"
                << "  - The filename is spelled correctly.\n"
                << "  - The image file is in the same folder as the program.\n"
                << "  - The extension is a supported type: .jpg, .png, .bmp, or .tga.\n";
        cerr << "Please try again.\n";
        i = loadANewImage();
    }
    return i;
}

void grayscale(Image &image1) {
    //Done by Ebrahem Hassan
    for (int i = 0; i < image1.width; i++) {
        for (int j = 0; j < image1.height; j++) {
            unsigned int avg = 0;
            for (int k = 0; k < 3; k++) {
                avg += image1(i, j, k);
            }
            avg /= 3;
            image1(i, j, 0) = avg;
            image1(i, j, 1) = avg;
            image1(i, j, 2) = avg;
        }
    }
}

void invert (Image &image) {
    // Done by youssef Ibrahim
    for (int i=0 ; i<image.width ; i++) {
        for (int j=0 ; j<image.height ; j++) {
            for (int k=0 ; k<image.channels ; k++) {
                image(i,j,k)= 255 - image(i,j,k);
            }
        }
    }
}


Image resizingImage(const Image &image1, int width, int height) {
    //Done by Ebrahem Hassan
    float xfaxtor = (float) image1.width / width, yfactor = (float) image1.height / height;
    Image resized(width, height);
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            for (int k = 0; k < 3; k++) {
                resized(i, j, k) = image1(round(i * xfaxtor), round(j * yfactor), k);
            }
        }
    }
    return resized;
}

Image mergeImage(Image image1) {
    //Done by Ebrahem Hassan
    cout << "Loading the second image to merge...";
    Image image2 = loadANewImage();
    if (image1.width == image2.width && image1.height == image2.height) {
        Image merged(image1.width, image1.height);
        for (int i = 0; i < image1.width; i++) {
            for (int j = 0; j < image1.height; j++) {
                for (int k = 0; k < 3; k++) {
                    merged(i, j, k) = (image1(i, j, k) + image2(i, j, k)) / 2;
                }
            }
        }
        return merged;
    }
    else {
        int choice;
        cout << "The images have different sizes. Please choose a merge option:\n"
                << "1. Resize to fit (enlarges the smaller image to match the largest).\n"
                << "2. Merge common area (merges only the overlapping top-left corner).\n"
                << "Enter your choice (1 or 2): ";
        cin >> choice;
        if (choice == 1) {
            int newWidth = max(image1.width, image2.width), newHeight = max(image1.height, image2.height);
            image1 = resizingImage(image1, newWidth, newHeight);
            image2 = resizingImage(image2, newWidth, newHeight);
            Image merged(newWidth, newHeight);
            for (int i = 0; i < newWidth; i++) {
                for (int j = 0; j < newHeight; j++) {
                    for (int k = 0; k < 3; k++) {
                        merged(i, j, k) = (image1(i, j, k) + image2(i, j, k)) / 2;
                    }
                }
            }
            return merged;
        }
        else if (choice == 2) {
            int minWidth = min(image1.width, image2.width);
            int minHeight = min(image1.height, image2.height);

            Image merged(minWidth, minHeight);

            for (int i = 0; i < minWidth; ++i) {
                for (int j = 0; j < minHeight; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        merged(i, j, k) = (image1(i, j, k) + image2(i, j, k)) / 2;
                    }
                }
            }
            return merged;
        }
        else {
            cout << "Invalid choice. Returning to menu.\n";
            return image1;
        }
    }
}

void saveTheImage(Image &i) {
    //Done by Ebrahem Hassan
    cout << "Please enter the filename to save your image as (e.g., result.png): ";
    string s;
    cin >> s;
    try {
        i.saveImage(s);
        cout << "Image saved successfully!\n";
        cout << "--> IMPORTANT: Please close the image viewer to return to the main menu. <--\n";
        system(s.c_str());
    } catch (const invalid_argument &e) {
        cerr << "Could not save the image. Please check the filename:\n"
                << "  - It must not contain spaces.\n"
                << "  - It must end with .jpg, .png, .bmp, or .tga.\n";
        cerr << "Please try again.\n";
        saveTheImage(i);
    }
}

void rotate(Image &img){
    // Done by youssef Ibrahim
    vector <string>options = {"If you want to rotate 90 deg press 1", "If you want to rotate 180 deg press 2" , "If you want to rotate 270 deg press 3"};
    for (int i = 0; i < options.size(); i++) {
        cout << options[i] << endl;
    }
    int x;
    cin >> x;
    if (x==1){
        int newWidth = img.height;
        int newHeight = img.width;
        Image newImage(newWidth, newHeight);
        for (int i = 0; i < img.width; i++) {
            for (int j = 0; j < img.height; j++) {
                for (int k = 0; k < 3; k++) {
                    newImage(img.height-1-j, i, k) = img(i, j, k);
                }
            }
        }
        img=newImage;
    }
    else if (x==2) {
        int width = img.width;
        int height = img.height;
        Image newImage(width, height);
        for (int i = 0; i < img.width; i++) {
            for (int j = 0; j < img.height; j++) {
                for (int k = 0; k < 3; k++) {
                    newImage(width - 1 - i, height - 1 - j, k) = img(i, j, k);
                }
            }
        }
        img=newImage;
    }
    else if (x==3) {
        int newWidth = img.height;
        int newHeight = img.width;
        Image newImage(newWidth, newHeight);
        for (int i = 0; i < img.width; i++) {
            for (int j = 0; j < img.height; j++) {
                for (int k = 0; k < 3; k++) {
                    newImage(j, img.width-1-i, k) = img(i, j, k);
                }
            }
        }
        img=newImage;
    }
}
int main() {
    cout << "Welcome to the Our Image Processor!" << endl;
    Image image = loadANewImage();

    while (true) {
        int option = mainMenu();
        switch (option) {
            case 1: // Load New Image
                image = loadANewImage();
                break;
            case 2: // Grayscale
                grayscale(image);
                cout << "Grayscale filter applied.\n";
                break;
            case 3://black and white

                break;
            case 4://invert image
                invert(image);
                break;
            case 5: // Merge
                image = mergeImage(image);
                cout << "Merge filter applied.\n";
                break;
            case 6://flip

                break;
            case 7://Rotate
                rotate(image);
                break;
            case 8: {
                // Resize
                cout << "Please enter the new dimensions." << endl;
                cout << "New width: ";
                int rswidth, rsheight;
                cin >> rswidth;
                cout << "New height: ";
                cin >> rsheight;
                image = resizingImage(image, rswidth, rsheight);
                cout << "Image resized.\n";
                break;
            }
            case 9: // Save
                saveTheImage(image);
                break;
            case 10: // Exit
                cout << "Thank you for using the image processor. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid option. Please choose a number from 1 to 10." << endl;
                break;
        }
    }

    return 0;
}
