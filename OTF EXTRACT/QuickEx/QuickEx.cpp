#include "QuickEx.h"


int main()
{
    int OperatorsLength = 2;
    QXOperatorArrayEntry OperatorsArray[]{
        {'d',QXOperator0},{'S',QXOperator1}
    };

    GlobalOperatorTable.RegisterOperatorsArray(OperatorsArray, OperatorsLength);

    QX MatchInfo("([0-9])", "123a48");
    

}