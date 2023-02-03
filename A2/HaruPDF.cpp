/*
 * George Benyeogor
 * CS3505
 * A2: Classes, Facades, and Makefiles
 * This class defines methods that allows the user to initialize a PDF,
 * write to that PDF, and then save the PDF.
 */
#include "HaruPDF.h"

/// @brief This constructor initializes everything needed to write to a PDF.
/// @param name_of_pdf The name of the PDF that will be written to.
HaruPDF::HaruPDF(char *nameOfPDF)
{
    strcpy(fname_, nameOfPDF);
    strcat(fname_, ".pdf");
    pdf_ = HPDF_New(NULL, NULL);
    // Adds a new page object
    page_ = HPDF_AddPage(pdf_);
    HPDF_Page_SetSize(page_, HPDF_PAGE_SIZE_A5, HPDF_PAGE_PORTRAIT);
    HPDF_Page_BeginText(page_);
    // Set the font
    font_ = HPDF_GetFont(pdf_, "Courier-Bold", NULL);
    HPDF_Page_SetTextLeading(page_, 20);
    HPDF_Page_SetGrayStroke(page_, 0);
    HPDF_Page_SetFontAndSize(page_, font_, 30);
}

/// @brief This method sets and displays the text on the PDF.
/// It utilizes a method that defines where any following text will be placed.
/// @param rad1 The angle of the text.
/// @param x The x coordinate of the text.
/// @param y The y coordinate of the text.
/// @param buf A char pointer that contains the text that will be displayed on the page.
void HaruPDF::setAndShowText(float rad1, float x, float y, char *buf)
{
    // This ugly function defines where any following text will be placed
    // on the page. The cos/sin stuff defines a 2D rotation
    // matrix.
    HPDF_Page_SetTextMatrix(page_,
                            cos(rad1), sin(rad1), -sin(rad1), cos(rad1),
                            x, y);
    HPDF_Page_ShowText(page_, buf);
}

/// @brief The destructor for the HaruPDF class.
HaruPDF::~HaruPDF()
{
    HPDF_Page_EndText(page_);
    /* save the document to a file */
    HPDF_SaveToFile(pdf_, fname_);
    /* clean up */
    HPDF_Free(pdf_);
}
