using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CS451Compiler
{

    class LexicalAnalyzer
    {

        /*Data Fields*/
        public Token tokenType;
        private Character characterType;
        private char previousChar;
        private char currentChar;
        private char nextChar;
        public string lexeme;
        private char[] charSequence;
        private int charSequenceIndex;

        public LexicalAnalyzer(char[] tokenSequence) {
            charSequence = tokenSequence;
            previousChar = ' ';
            currentChar = tokenSequence[0];
            nextChar = tokenSequence[1];
            lexeme = string.Empty;
            charSequenceIndex = 0;
        }

        void getNonBlank()
        {
            while (currentChar == ' ')
            {
                ItterateNextCharacter();
            }
        }

        private void ItterateNextCharacter()
        {
            previousChar = currentChar;
            charSequenceIndex++;
            currentChar = charSequence[charSequenceIndex];
            if(charSequenceIndex != charSequence.Length - 1)
            {
                nextChar = charSequence[charSequenceIndex + 1];
            }
        }

        private Character DetermineCharacterType()
        {
            if(Char.IsDigit(currentChar))
            {
                return Character.DIGIT;
            }
            if(Char.IsLetter(currentChar))
            {
                return Character.LETTER;
            }
            return Character.UNKNOWN;
        }

        private Token DetermineTokenType()
        {
            Token currentToken;
            switch (currentChar)
            {
                case '(':
                    currentToken = Token.LEFT_PAREN;
                    break;

                case ')':
                    currentToken = Token.RIGHT_PAREN;
                    break;

                case '+':
                    currentToken = Token.ADD_OP;
                    break;

                case '-':
                    currentToken = Token.SUB_OP;
                    break;

                case '*':
                    currentToken = Token.MULT_OP;
                    break;

                case '/':
                    currentToken = Token.DIV_OP;
                    break;

                default:
                    currentToken = Token.UNKNOWN;
                    break;
            }
            return currentToken;
        }

        public bool AnalyzeNextlexeme()
        {
            if(charSequenceIndex == charSequence.Length)
            {
                return false;
            }
            getNonBlank();
            characterType = DetermineCharacterType();
            tokenType = Token.UNKNOWN;
            lexeme = "";
            switch (characterType)
            {

                /* Parse identifiers */
                case Character.LETTER:
                    while (characterType == Character.LETTER || characterType == Character.DIGIT || currentChar == '_')
                    {
                        lexeme += currentChar.ToString();
                        ItterateNextCharacter();
                        characterType = DetermineCharacterType();
                    }
                    if (lexeme == "for")
                    {
                        tokenType = Token.FOR_CODE;
                        break;
                    }
                    else if (lexeme == "if")
                    {
                        tokenType = Token.IF_CODE;
                        break;
                    }
                    else if (lexeme == "else")
                    {
                        tokenType = Token.ELSE_CODE;
                        break;
                    }
                    else if (lexeme == "while")
                    {
                        tokenType = Token.WHILE_CODE;
                        break;
                    }
                    else if (lexeme == "do")
                    {
                        tokenType = Token.DO_CODE;
                        break;
                    }
                    else if (lexeme == "int")
                    {
                        tokenType = Token.INT_CODE;
                        break;
                    }
                    else if (lexeme == "float")
                    {
                        tokenType = Token.FLOAT_CODE;
                        break;
                    }
                    else if (lexeme == "switch")
                    {
                        tokenType = Token.SWITCH_CODE;
                        break;
                    }
                    else
                    {
                        tokenType = Token.IDENT;
                        break;
                    }

                /* Parse integer literals */
                case Character.DIGIT:
                    while (characterType == Character.DIGIT)
                    {
                        lexeme += currentChar.ToString();
                        ItterateNextCharacter();
                    }
                    break;

                /* Parentheses and operators */
                case Character.UNKNOWN:
                    ItterateNextCharacter();
                    break;

                default :
                    break;

            } /* End of switch */

            return true;
        }


    }
}
