#include <complex>
#include <iostream>
#include <vector>
using namespace std;
#include "Image_Class.h"
#include <limits>
//=========================================================================
//                            MAIN MENU FUNCTION
//=========================================================================
int mainMenu()
{
    // Done by Ebrahem Hassan
    string menu[14] = {
        "Load New Image", "Grayscale Filter", "Black and White filter", "Invert Image", "Merge Images", "Flip Image", "Rotate Image","Frame","Edge Detecting",
        "Resize Image","Blur","Sun Light Effect ", "Save Image", "Exit"};
    int choice;
    cout << "\nPlease select an option:" << endl;
    for (int i = 0; i < 14; i++)
    {
        cout << i + 1 << ". " << menu[i] << endl;
    }
    cout << "Enter choice: ";
    cin >> choice;
    while (true){
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    }
        else {break;}
    }
    return choice;
}
//=========================================================================
//                            LOAD IMAGE FUNCTION
//=========================================================================
Image loadANewImage()
{
    // Done by Ebrahem hassan
    cout << "Please enter the filename of the image to load (e.g., photo.jpg): ";
    string filename;
    cin >> filename;
    Image i;
    try
    {
        i.loadNewImage(filename);
    }
    catch (const invalid_argument &e)
    {
        cerr << "Error: Could not load the image. Please check the following:\n"
             << "  - The filename is spelled correctly.\n"
             << "  - The image file is in the same folder as the program.\n"
             << "  - The extension is a supported type: .jpg, .png, .bmp, or .tga.\n";
        cerr << "Please try again.\n";
        i = loadANewImage();
    }
    return i;
}
//=========================================================================
//                            GRAYSCALE FILTER
//=========================================================================
void grayscale(Image &image1)
{
    // Done by Ebrahem Hassan
    for (int i = 0; i < image1.width; i++)
    {
        for (int j = 0; j < image1.height; j++)
        {
            unsigned int avg = 0;
            for (int k = 0; k < 3; k++)
            {
                avg += image1(i, j, k);
            }
            avg /= 3;
            image1(i, j, 0) = avg;
            image1(i, j, 1) = avg;
            image1(i, j, 2) = avg;
        }
    }
}
//=========================================================================
//                         BLACK AND WHITE FILTER
//=========================================================================
void blackandwhite(Image &image)
{
    // Done by Mohamed Abdelmaqsoud
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg = 0;

            for (int k = 0; k < 3; ++k)
            {
                avg += image(i, j, k);
            }

            avg /= 3;

            unsigned int bw = (avg >= 128) ? 255 : 0;

            image(i, j, 0) = bw;
            image(i, j, 1) = bw;
            image(i, j, 2) = bw;
        }
    }
}
//=========================================================================
//                            INVERT FILTER
//=========================================================================
void invert(Image &image)
{
    // Done by youssef Ibrahim
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            for (int k = 0; k < image.channels; k++)
            {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
}
//=========================================================================
//                            Detect Edge FILTER
//=========================================================================
void detectEdge(Image &i) {//done by Ebrahem Hassan
    Image grayscaleImage=i,outputImage(i.width,i.height);
    grayscale(grayscaleImage);
    for (int i = 1; i < grayscaleImage.width-1; i++) {
        for (int j = 1; j < grayscaleImage.height-1; j++) {
            int gx=(grayscaleImage(i+1, j-1, 0)+2*grayscaleImage(i+1,j,0)+grayscaleImage(i+1,j+1,0))-(grayscaleImage(i-1, j-1, 0)+2*grayscaleImage(i-1,j,0)+grayscaleImage(i-1,j+1,0)),
             gy=(grayscaleImage(i-1, j+1, 0)+2*grayscaleImage(i,j+1,0)+grayscaleImage(i+1,j+1,0))-(grayscaleImage(i-1, j-1, 0)+2*grayscaleImage(i,j-1,0)+grayscaleImage(i+1,j-1,0));
            int diff=sqrt(gx*gx+gy*gy);
            if (diff>=128) {
                outputImage(i,j,0)=0;
                outputImage(i,j,1)=0;
                outputImage(i,j,2)=0;
            }
            else {
                outputImage(i,j,0)=255;
                outputImage(i,j,1)=255;
                outputImage(i,j,2)=255;
            }

        }
    }
    i=outputImage;
}
//=========================================================================
//                            RESIZE IMAGE
//=========================================================================
Image resizingImage(const Image &image1, int width, int height)
{
    // Done by Ebrahem Hassan
    float xfaxtor = (float)image1.width / width, yfactor = (float)image1.height / height;
    Image resized(width, height);
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                resized(i, j, k) = image1(round(i * xfaxtor), round(j * yfactor), k);
            }
        }
    }
    return resized;
}

//=========================================================================
//                            Frame FUNCTION
//=========================================================================
void frame(Image &image) {// Made by Youssef Ibrahim
    cout << "--- Please Choose a Frame Style ---" << endl;
    cout << "1. Simple Frame (Single Color)" << endl;
    cout << "2. Double Frame (Two Colors)" << endl;
    cout << "3. Elegant Frame (Matte with Spacing)" << endl;
    cout << "4. Decorative Image Frame" << endl;
int x;
    cin>>x;
    if(x==1) {
        int frameThickness = 20;
        char b_color=255;
        char g_color=0;
        char r_color=0;
        int newwidth=image.width+(frameThickness*2);
        int newheight=image.height+(frameThickness*2);
        Image framedImage(newwidth,newheight);
        for(int i=0;i<newwidth;i++) {
            for(int j=0;j<newheight;j++) {
                framedImage(i,j,0) = r_color;
                framedImage(i,j,1) = g_color;
                framedImage(i,j,2) = b_color;
            }
        }
        for(int i=0;i<image.width;i++) {
            for(int j=0;j<image.height;j++) {
                int startX = i+frameThickness;
                int startY = j+frameThickness;
                framedImage(startX,startY,0) = image(i,j,0);
                framedImage(startX,startY,1) = image(i,j,1);
                framedImage(startX,startY,2) = image(i,j,2);
            }
        }
        image = framedImage;
    }
    else if(x==2) {
        int outerframeThickness = 20;
        char outerB_color=255;
        char outerG_color=0;
        char outerR_color=0;
        int innerframeThickness = 10;
        char innerB_color=255;
        char innerG_color=255;
        char innerR_color=255;
        int totalBorderThickness = outerframeThickness + innerframeThickness;
        int newwidth=image.width+(totalBorderThickness*2);
        int newheight=image.height+(totalBorderThickness*2);
        Image framedImage(newwidth,newheight);
        for(int i=0;i<newwidth;i++) {
            for(int j=0;j<newheight;j++) {
                framedImage(i,j,0) = outerR_color;
                framedImage(i,j,1) = outerG_color;
                framedImage(i,j,2) = outerB_color;
            }
        }

        int startX = outerframeThickness;
        int startY = outerframeThickness;
                for(int i=outerframeThickness;i<newwidth - outerframeThickness;i++) {
                    for(int j=outerframeThickness;j<newheight - outerframeThickness;j++) {
                        framedImage(i,j,0) = innerR_color;
                        framedImage(i,j,1) = innerG_color;
                        framedImage(i,j,2) = innerB_color;
                    }
                }
        for(int i = 0 ; i < image.width; i++) {
            for(int j = 0 ; j < image.height; j++) {
                int start1X = i+totalBorderThickness;
                int start1Y = j+totalBorderThickness;
             framedImage(start1X,start1Y,0) = image(i,j,0);
                framedImage(start1X,start1Y,1) = image(i,j,1);
                framedImage(start1X,start1Y,2) = image(i,j,2);
            }
        }
        image = framedImage;
    }
    else if(x==3) {
        int outerframeThickness = 20;
        char outerB_color=255;
        char outerG_color=0;
        char outerR_color=0;
        int spacing = 5;
        char spaceB_color=0;
        char spaceG_color=0;
        char spaceR_color=0;
        int whiteFrame = 5;
        char white_R = 255;
        char white_G = 255;
        char white_B = 255;
        int totalFrameThickness = outerframeThickness + spacing + whiteFrame + spacing + whiteFrame;
        int newwidth=image.width+(totalFrameThickness*2);
        int newheight=image.height+(totalFrameThickness*2);
        Image framedImage(newwidth,newheight);
        for(int i=0;i<newwidth;i++) {
            for(int j=0;j<newheight;j++) {
                framedImage(i,j,0) = outerR_color;
                framedImage(i,j,1) = outerG_color;
                framedImage(i,j,2) = outerB_color;
            }
        }
        int currentBorder = outerframeThickness;
        for(int i=currentBorder;i<newwidth-currentBorder;i++) {
            for(int j=currentBorder;j<newheight-currentBorder;j++) {
                framedImage(i,j,0) = spaceB_color;
                framedImage(i,j,1) = spaceG_color;
                framedImage(i,j,2) = spaceR_color;
            }
        }
    currentBorder +=spacing;
        for(int i=currentBorder;i<newwidth-currentBorder;i++) {
            for(int j=currentBorder;j<newheight-currentBorder;j++) {
                framedImage(i,j,0) = white_R;
                framedImage(i,j,1) = white_G;
                framedImage(i,j,2) = white_B;
            }
        }
    currentBorder +=whiteFrame;
        for(int i=currentBorder;i<newwidth-currentBorder;i++) {
            for(int j=currentBorder;j<newheight-currentBorder;j++) {
                framedImage(i,j,0) = spaceR_color;
                framedImage(i,j,1) = spaceG_color;
                framedImage(i,j,2) = spaceB_color;
            }
        }
    currentBorder +=spacing;
        for(int i=currentBorder;i<newwidth-currentBorder;i++) {
            for(int j=currentBorder;j<newheight-currentBorder;j++) {
                framedImage(i,j,0) = white_R;
                framedImage(i,j,1) = white_G;
                framedImage(i,j,2) = white_B;
            }
        }
    currentBorder +=whiteFrame;
        for(int i=0;i<image.width;i++) {
            for(int j=0;j<image.height;j++) {
                int start1X = i+currentBorder;
                int start1Y = j+currentBorder;

                framedImage(start1X,start1Y,0) = image(i,j,0);
                framedImage(start1X,start1Y,1) = image(i,j,1);
                framedImage(start1X,start1Y,2) = image(i,j,2);
            }
        }
        image = framedImage;
    }
    if(x==4) {
        Image frame("FRAME.jpg");
        frame = resizingImage(frame, image.width, image.height);

        int frameThickness = 20 ;
        char b_color = 255;
        char g_color = 255;
        char r_color = 255;

        int newwidth = image.width;
        int newheight = image.height;
        Image framedImage = frame;

        for(int i=0;i<newwidth;i++) {
            for(int j=0;j<newheight;j++) {
                framedImage(i,j,0) = r_color;
                framedImage(i,j,1) = g_color;
                framedImage(i,j,2) = b_color;
            }
        }
        for (int i = frameThickness; i < newwidth - frameThickness; i++) {
            for (int j = frameThickness; j < newheight - frameThickness; j++) {

                if (frame(i, j, 0) > 230 && frame(i, j, 1) > 230 && frame(i, j, 2) > 230) {

                    for (int k = 0; k < 3; k++) {
                        framedImage(i, j, k) = image(i, j, k);
                    }
                }
                }
        }

        image = framedImage;
    }

}





//=========================================================================
//                            MERGE FILTER
//=========================================================================
Image mergeImage(Image image1)
{
    // Done by Ebrahem Hassan
    cout << "Loading the second image to merge...";
    Image image2 = loadANewImage();
    if (image1.width == image2.width && image1.height == image2.height)
    {
        Image merged(image1.width, image1.height);
        for (int i = 0; i < image1.width; i++)
        {
            for (int j = 0; j < image1.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    merged(i, j, k) = (image1(i, j, k) + image2(i, j, k)) / 2;
                }
            }
        }
        return merged;
    }
    else
    {
        int choice;
        cout << "The images have different sizes. Please choose a merge option:\n"
             << "1. Resize to fit (enlarges the smaller image to match the largest).\n"
             << "2. Merge common area (merges only the overlapping top-left corner).\n"
             << "Enter your choice (1 or 2): ";
        cin >> choice;
        if (choice == 1)
        {
            int newWidth = max(image1.width, image2.width), newHeight = max(image1.height, image2.height);
            image1 = resizingImage(image1, newWidth, newHeight);
            image2 = resizingImage(image2, newWidth, newHeight);
            Image merged(newWidth, newHeight);
            for (int i = 0; i < newWidth; i++)
            {
                for (int j = 0; j < newHeight; j++)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        merged(i, j, k) = (image1(i, j, k) + image2(i, j, k)) / 2;
                    }
                }
            }
            return merged;
        }
        else if (choice == 2)
        {
            int minWidth = min(image1.width, image2.width);
            int minHeight = min(image1.height, image2.height);

            Image merged(minWidth, minHeight);

            for (int i = 0; i < minWidth; ++i)
            {
                for (int j = 0; j < minHeight; ++j)
                {
                    for (int k = 0; k < 3; ++k)
                    {
                        merged(i, j, k) = (image1(i, j, k) + image2(i, j, k)) / 2;
                    }
                }
            }
            return merged;
        }
        else
        {
            cout << "Invalid choice. Returning to menu.\n";
            return image1;
        }
    }
}
//=========================================================================
//                            FLIP FILTER
//=========================================================================
void flip(Image &image)
{ // Done by Mohamed Abdelmaqsoud

    Image flipped(image.width, image.height);

    char c;
    cout << "Enter flip type (H for horizontal, V for vertical): ";
    cin >> c;

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                if (c == 'H'||c == 'h')
                {
                    flipped(image.width - 1 - i, j, k) = image(i, j, k);
                }
                else if (c == 'V'||c == 'v')
                {
                    flipped(i, image.height - 1 - j, k) = image(i, j, k);
                }
            }
        }
    }
    image = flipped;
}
//=========================================================================
//                            Blur FILTER
//=========================================================================

void blur(Image &img) {//Done by Youssef Ibrahim
    int scale;
    do {
        cout << "Please enter blur scale (a value from 0 to 100): ";
        cin >> scale;
    } while (scale < 0 || scale > 100);
    if (scale == 0) {
        return;
    }

    scale = (scale * 40.0) / 100;


    Image horizontally_blurred_img(img.width, img.height);

    for (int j = 0; j < img.height; ++j) {
        for (int i = 0; i < img.width; ++i) {
            long long sumRed = 0, sumGreen = 0, sumBlue = 0;
            int pixelCount = 0;

            for (int k = i - scale; k <= i + scale; ++k) {
                if (k >= 0 && k < img.width) {
                    sumRed   += img(k, j, 0);
                    sumGreen += img(k, j, 1);
                    sumBlue  += img(k, j, 2);
                    pixelCount++;
                }
            }

            horizontally_blurred_img(i, j, 0) = sumRed / pixelCount;
            horizontally_blurred_img(i, j, 1) = sumGreen / pixelCount;
            horizontally_blurred_img(i, j, 2) = sumBlue / pixelCount;
        }
    }

    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            long long sumRed = 0, sumGreen = 0, sumBlue = 0;
            int pixelCount = 0;

            for (int l = j - scale; l <= j + scale; ++l) {
                if (l >= 0 && l < img.height) {
                    sumRed   += horizontally_blurred_img(i, l, 0);
                    sumGreen += horizontally_blurred_img(i, l, 1);
                    sumBlue  += horizontally_blurred_img(i, l, 2);
                    pixelCount++;
                }
            }
            img(i, j, 0) = sumRed / pixelCount;
            img(i, j, 1) = sumGreen / pixelCount;
            img(i, j, 2) = sumBlue / pixelCount;
        }
    }
}



//=========================================================================
//                            Sun Effect FILTER
//=========================================================================
void sunEffect(Image &image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {

            int brightness = (image(i, j, 0) +  image(i, j, 1) + image(i, j, 2)) / 3;
            int redToAdd = brightness /3 ;
            int greenToAdd = brightness / 4;

            if (image(i,j,0) +redToAdd> 255) {
                image(i,j,0) = 255;
            }
            else {
                image(i,j,0) +=redToAdd;
            }
            if (image(i,j,1) +greenToAdd> 255) {
                image(i,j,1) = 255;
            }
            else {
                image(i,j,1) +=greenToAdd;
            }
        }
    }
}
//=========================================================================
//                            SAVE IMAGE FUNCTION
//=========================================================================
void saveTheImage(Image &i)
{
    // Done by Ebrahem Hassan
    cout << "Please enter the filename to save your image as (e.g., result.png): ";
    string s;
    cin >> s;
    try
    {
        i.saveImage(s);
        cout << "Image saved successfully!\n";
        cout << "--> IMPORTANT: Please close the image viewer to return to the main menu. <--\n";
        system(s.c_str());
    }
    catch (const invalid_argument &e)
    {
        cerr << "Could not save the image. Please check the filename:\n"
             << "  - It must not contain spaces.\n"
             << "  - It must end with .jpg, .png, .bmp, or .tga.\n";
        cerr << "Please try again.\n";
        saveTheImage(i);
    }
}
//=========================================================================
//                            ROTATE FILTER
//=========================================================================
void rotate(Image &img)
{
    // Done by youssef Ibrahim
    vector<string> options = {"If you want to rotate 90 deg press 1", "If you want to rotate 180 deg press 2", "If you want to rotate 270 deg press 3"};
    for (int i = 0; i < options.size(); i++)
    {
        cout << options[i] << endl;
    }
    int x;
    cin >> x;
    if (x == 1)
    {
        int newWidth = img.height;
        int newHeight = img.width;
        Image newImage(newWidth, newHeight);
        for (int i = 0; i < img.width; i++)
        {
            for (int j = 0; j < img.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    newImage(img.height - 1 - j, i, k) = img(i, j, k);
                }
            }
        }
        img = newImage;
    }
    else if (x == 2)
    {
        int width = img.width;
        int height = img.height;
        Image newImage(width, height);
        for (int i = 0; i < img.width; i++)
        {
            for (int j = 0; j < img.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    newImage(width - 1 - i, height - 1 - j, k) = img(i, j, k);
                }
            }
        }
        img = newImage;
    }
    else if (x == 3)
    {
        int newWidth = img.height;
        int newHeight = img.width;
        Image newImage(newWidth, newHeight);
        for (int i = 0; i < img.width; i++)
        {
            for (int j = 0; j < img.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    newImage(j, img.width - 1 - i, k) = img(i, j, k);
                }
            }
        }
        img = newImage;
    }
}

//=========================================================================
//                            MAIN PROGRAM
//=========================================================================
int main()
{
    cout << "Welcome to the Our Image Processor!" << endl;
    Image image = loadANewImage();

    while (true)
    {
        int option = mainMenu();
        switch (option)
        {
        case 1: // Load New Image
            image = loadANewImage();
            break;
        case 2: // Grayscale
            grayscale(image);
            cout << "Grayscale filter applied.\n";
            break;
        case 3: // black and white
            blackandwhite(image);
            cout << "Black and White filter applied.\n";
            break;
        case 4: // invert image
            invert(image);
            cout << "Invert filter applied.\n";
            break;
        case 5: // Merge
            image = mergeImage(image);
            cout << "Merge filter applied.\n";
            break;
        case 6: // flip
            flip(image);
            cout << "Flip filter applied.\n";
            break;
        case 7: // Rotate
            rotate(image);
            cout << "Rotate filter applied.\n";
            break;
        case 8://Frame image
            frame(image);
            cout << "Frame filter applied.\n";
            break;
        case 9://detect image
            detectEdge(image);
            cout << "Detect Edge filter applied.\n";
            break;
        case 10:
        {
            // Resize
            cout << "Please enter the new dimensions." << endl;
            cout << "New width: ";
            int rswidth, rsheight;
            cin >> rswidth;
            cout << "New height: ";
            cin >> rsheight;
            image = resizingImage(image, rswidth, rsheight);
            cout << "Image resized.\n";
            cout<<"Resize applied!";
            break;
        }
        case 11://Blur
            blur(image);
            cout << "Blur filter applied.\n";
            break;
        case 12://Sun Light Effect
            sunEffect(image);
            cout << "Sun Effect applied! .\n";
            break;
        case 13: // Save
            saveTheImage(image);
            break;
        case 14: // Exit
            cout << "Thank you for using the image processor. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid option. Please choose a number from 1 to 10." << endl;
            break;
        }
    }

    return 0;
}
