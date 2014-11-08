#include "hyphen.h"

int main()
{
    using namespace hyphen;

    // basics
    the Strings = {"1", "2", "3", "4", "5", "6"};
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
    the OldErrors = loaded-from-"old_errorlist.xml";
    the NewErrors = loaded-from-"new_errorlist.xml";

    the OldErrorsList = OldErrors-split-with-"<error id=";
    for( the ErrorEntry : OldErrorsList ){
        the ErrorID = (ErrorEntry-split-with-" ")[1];
        memorize-ErrorID;
    }

    the Report = "New error IDs are:";
    the NewErrorList = NewErrors-split-with-"<error id=";
    for( the ErrorEntry : NewErrorList ){
        the ErrorID = (ErrorEntry-split-with-" ")[1];
        if( not (remember-ErrorID) ){
            Report = Report & "\n\t" & ErrorID;
        }
    }

    save-Report-to-"novel_errors.txt";
    print-it;

    return 0;
}
