/*
 *George Benyeogor
 *CS3505
 *A2: Classes, Facades, and Makefiles
 */

#include "HaruPDF.h"
#include "Spiral.h"

/// @brief The driver method that combines HaruPDF and Spiral to
/// draw user input provided from the command line in the shape of a Spiral onto a PDF.
/// @param argc The number of arguments passed in from the command line.
/// @param argv All the arguments passed in from the command line stored in a char array.
/// @return An int.
int main(int argc, char **argv)
{
    // check if given a second argument
    if (argc < 2)
        return 0;
    else
    {
        HaruPDF pdf(argv[0]);
        float x = 210;
        float y = 300;
        float angle = 360;
        float scale = .15;
        Spiral spiral(x, y, angle, scale);
        const char *text = argv[1];

        // The loop that draws the spiral onto the PDF
        for (unsigned int i = 0; i < strlen(text); i++)
        {
            char buf[2];
            buf[0] = text[i];
            buf[1] = 0;
            pdf.setAndShowText(spiral.getRad1(), spiral.getSpiralX(), spiral.getSpiralY(), buf);
            spiral.changeRadius();
            spiral += 1080/spiral.getRadius();
        }
        return 0;
    }
}