#include "hyphen.h"

int main()
{
    using namespace hyphen;

    // basics
    the Strings = {"1", "2", "3", "4", "5", "6"};
    print-Strings;
    for(the A : Strings){
        the B = "B = " & A;
        print-B;
    }

    the Matrix = {  {1, 2, 3},
                    {4, 5, 6}};

    print-("Matrix 2,3 = " & Matrix[2][3]);

    // text processing example
    the String = "0 1 2 3 4 5 6 7 8 9";
    the Numbers = String-split-with-" ";
    the Some = Numbers-elements-(from-2-to-(last-of-Numbers - 1));
    print-("From 1 to 8: " & (Some-joined-with-", "));


    // file processing example
    the IDsToCheck = {"outOfBounds", "negativeIndex", "fakeError"};

    the Text = loaded-from-"errorlist_example.xml";

    the Lines = Text-split-with-"<error id=";
    the LinesWithoutXMLHeader = Lines-elements-(from-2-to-(last-of-Lines));
    for( the Line : LinesWithoutXMLHeader ){
        the ErrorID = (Line-split-with-" ")[1];
        memorize-ErrorID;
    }

    the Report = "Checked error IDs:";
    for( the ID : IDsToCheck ){
        if( remember-(ID-in-quotemarks) ){
            Report = Report & "\n\t" & ID & " is in error list;";
        }else{
            Report = Report & "\n\t" & ID & " is not.";
        }
    }

    save-Report-to-"checked_errors.txt";
    print-it;


    return 0;
}
