#include "../inc/part_of_the_matrix.h"

void evaluateExpression(char *operand1Str, char operation, char *operand2Str, char *resultStr, int index) 
{
    if (resultStr[index] == '\0')
    {
        int operand1 = mx_atoi(operand1Str);
        int operand2 = mx_atoi(operand2Str); 

        int expected_result = mx_atoi(resultStr);
        int computedResult;
        switch(operation) 
        {
            case '+': computedResult = operand1 + operand2; break;
            case '-': computedResult = operand1 - operand2; break;
            case '*': computedResult = operand1 * operand2; break;
            case '/': if (operand2 == 0) computedResult = MX_INT_MAX;
                      else computedResult = operand1 / operand2; break;
            default: computedResult = MX_INT_MAX;;
        }

        if (computedResult == expected_result)
        {
        mx_printint(operand1);
        mx_printchar(' ');
        mx_printchar(operation);
        mx_printchar(' ');
        mx_printint(operand2);
        mx_printchar(' ');
        mx_printchar('=');
        mx_printchar(' ');
        mx_printint(computedResult);
        mx_printchar('\n');
        }
        return;
    }

    if (resultStr[index] == '?') 
    {
        for (char digit = '0'; digit <= '9'; digit++) 
        {
            resultStr[index] = digit;
            evaluateExpression(operand1Str, operation, operand2Str, resultStr, index + 1);
        }
        resultStr[index] = '?';
    } 
    else 
    {
        evaluateExpression(operand1Str, operation, operand2Str, resultStr, index + 1);
    }
}


void generateAndEvaluateCombinationsForOperands(char *operand1, char *operand2, int index, char operation, char *result, bool isOperand1) 
{
    char *currentOperand = isOperand1 ? operand1 : operand2;
    if (currentOperand[index] == '\0') 
    {
        if (isOperand1) 
        {
            generateAndEvaluateCombinationsForOperands(operand1, operand2, 0, operation, result, false);
        } 
        else 
        {

            evaluateExpression(operand1, operation, operand2, result, 0);

        }
        return;
    }

    if (currentOperand[index] == '?') 
    {
        for (char digit = '0'; digit <= '9'; digit++) 
        {
            currentOperand[index] = digit;
            generateAndEvaluateCombinationsForOperands(operand1, operand2, index + 1, operation, result, isOperand1);
        }
        currentOperand[index] = '?';
    } 
    else 
    {
        generateAndEvaluateCombinationsForOperands(operand1, operand2, index + 1, operation, result, isOperand1);
    }
}

void tryReplaceAndEvaluate(char *operand1, char *operand2, char operation, char *result) 
{
    char originalOperand1[mx_strlen(operand1) + 1];
    char originalOperand2[mx_strlen(operand2) + 1];
    
    mx_strcpy(originalOperand1, operand1);
    mx_strcpy(originalOperand2, operand2);
    
    generateAndEvaluateCombinationsForOperands(operand1, operand2, 0, operation, result, true);

    mx_strcpy(operand1, originalOperand1);
    mx_strcpy(operand2, originalOperand2);
}
                

bool isValidOperandOrResult(const char* operand)
{
    int i = 0;
    while (operand[i] == ' ') i++;

	for (; operand[i] != '\0'; i++) 
	{
        if (!mx_isdigit(operand[i]) && operand[i] != '?' && !mx_isspace(operand[i]) && operand[i] != '-') 
        {
            return false;
        }
    }
    	return true;
}


char isValidOperation(const char* operation)
{
    int i = 0;
    while (operation[i] == ' ') i++;

    if (operation[i] != '+' && operation[i] != '-' && operation[i] != '*' 
        && operation[i] != '/' && operation[i] != '?') return ' ';

    int pos = i;

    i++;
    while (operation[i] != '\0')
    {
        if (operation[i] != ' ') return ' ';
        i++;
    }

    return operation[pos];
}

int main(int argc, char *argv[]) {
    	if (argc != 5)
	{
		mx_printerr("usage: ./part_of_the_matrix [operand1] [operation] [operand2] [result]\n");
		exit(1);
	}

    	char *operand1 = argv[1];
    	char *operation = argv[2];
    	char *operand2 = argv[3];
    	char *result = argv[4];
    	char op;

    	if (isValidOperation(operation) == ' ') 
    	{
        	mx_printerr("Invalid operation: ");
        	mx_printerr(operation);
        	mx_printchar('\n');
        	exit(1);
    	}
    	else 
    		op = isValidOperation(operation);

    	if (!isValidOperandOrResult(operand1)) 
    	{
        	mx_printerr("Invalid operand: ");
        	mx_printerr(operand1);
        	mx_printchar('\n');
        	exit(1);
    	}

    	if (!isValidOperandOrResult(operand2)) 
    	{
        	mx_printerr("Invalid operand: ");
        	mx_printerr(operand2);
        	mx_printchar('\n');
        	exit(1);
    	}

    	if (!isValidOperandOrResult(result)) {
		mx_printerr("Invalid result: ");
		mx_printerr(result);
		mx_printchar('\n');
        	exit(1);
    	}
    	if (op != '?')
		tryReplaceAndEvaluate(operand1, operand2, op, result);
	else
	{
		tryReplaceAndEvaluate(operand1, operand2, '+', result);
		tryReplaceAndEvaluate(operand1, operand2, '-', result);
		tryReplaceAndEvaluate(operand1, operand2, '*', result);
		tryReplaceAndEvaluate(operand1, operand2, '/', result);
	}
   	return 0;
}
