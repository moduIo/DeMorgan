//--------------------------------------------------------------
// Predictive parser implementation for logical expressions.
//
// BNF:
//______________________________________________________________
// Left Recursive Grammar 
//
// expression ->  ! {print('!')} expression
//             |  ( {print('(')} expression ) {print(')')}
//	       |  expression & {print('&')} expression
//             |  expression | {print('|')} expression
//             |  proposition
//
// proposition ->  a {print('a')}
//              |  b {print('b')}
//              |  ... 
//              |  z {print('z')}
//
//______________________________________________________________
// Right Recursive Grammar
//
// expression ->  proposition rest
//             |  ! {print('!')} expression
//             |  ( {print('(')} expression ) {print(')')} 
//
// rest ->  & {print('&')} expression rest
//       |  | {print('|')} expression rest
//       |  epsilon
//
// proposition ->  a {print('a')}
//              |  b {print('b')}
//              |  ...
//              |  z {print('z')}
//--------------------------------------------------------------
#include <iostream>
#include <boost/algorithm/string.hpp>

using namespace std;

//--------------------------------------------------------------
// Signatures.
//--------------------------------------------------------------
void expression();
void proposition();
void rest();
void epsilon();
void next();
void print(char);
void match(char);

//--------------------------------------------------------------
// Global variables.
// Sorry.
//--------------------------------------------------------------
string lookahead;  
int i;

//--------------------------------------------------------------
//  Main.
//--------------------------------------------------------------
int main(){        
    i = 0;  
    getline(cin, lookahead);
    boost::erase_all(lookahead, " ");
            
    cout << "\n\n\n";
    
    //De Morgan's law...        
    print('!');
    print('(');

    expression();
        
    print(')');
    
    cout << "\n\n";
    
    return 0;
}

//--------------------------------------------------------------
// Parses expression production.
//--------------------------------------------------------------
void expression(){
    switch(lookahead[i]){
        case '!':
            print('!');
            print('!');
            next();
            expression();
            break;
            
        case '(':
            print('(');
            next();
            expression();
            match(')');
            break;
            
        default:
            proposition();
            rest();
            break;
    }
}

//--------------------------------------------------------------
// Parses proposition production.
//--------------------------------------------------------------
void proposition(){
    // If lookahead in {a, b, c, ..., z}
    if (lookahead[i] >= 97 && lookahead[i] <= 122){
        print('!');
        cout << lookahead[i] << ' ';        
        next();   
    }
    else {
        cout << "\nInvalid input: " << lookahead[i] << ".\n\n";
        exit(1);
    }
}

//--------------------------------------------------------------
// Parses rest production.
//--------------------------------------------------------------
void rest(){
    switch(lookahead[i]){
        case '&':
            print('|');
            next();
            expression();
            rest();
            break;
        
        case '|':
            print('&');
            next();
            expression();
            rest();
            break;
            
        default: 
            epsilon();
            break;
    }
}

//--------------------------------------------------------------
// Checks for invalid input.  Else, does nothing.
//--------------------------------------------------------------
void epsilon(){
    if (lookahead[i] != ')' && lookahead[i] != '\0'){
        cout << "\nInvalid input: " << lookahead[i] << ".\n\n";
        exit(1);
    }
}

//--------------------------------------------------------------
// Method retrieves next character for parsing.
//--------------------------------------------------------------
void next(){ i++; }

//--------------------------------------------------------------
// Method outputs character to console.
//--------------------------------------------------------------
void print(char c){
    cout << c << ' ';    
}

//--------------------------------------------------------------
// Method validates character input.
//--------------------------------------------------------------
void match(char c){
    if (lookahead[i] == c){
        cout << c << ' ';
        next();
    }
    else {
        cout << "\nInvalid input: " << lookahead[i] << ".\n\n";
        exit(1);
    }
}