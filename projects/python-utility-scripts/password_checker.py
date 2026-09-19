#Task 3: Password Strength Checker
#Objective: Create a script that evaluates password strength based on specific rules.

#Requirements:

#Minimum 8 characters.
#At least one uppercase letter, one lowercase letter, one number, and one special character.
#Provide feedback on what’s missing in weak passwords.
#Suggested Libraries:

#re (for pattern matching)

import re
import getpass

pCASE = r'[A-Z]'

pcase = r'[a-z]'

pnumber = r'\d'

plength = r'.{8,}'

pschar = r'[!@#$%^&*(),.?":{}|<>]'


def check_password(password):
    missing_requirements = []
    weak = 0
    if not re.search(pCASE, password):
        weak += 1
        missing_requirements.append("At least one uppercase letter")
    if not re.search(pcase, password):
        weak += 1
        missing_requirements.append("At least one lowercase letter")
    if not re.search(plength, password):
        weak += 1
        missing_requirements.append("Minimum length of 8")
    if not re.search(pnumber, password):
        weak += 1
        missing_requirements.append("At least one number")
    if not re.search(pschar, password):
        weak += 1
        missing_requirements.append("At least one special character")
    strength = 5 - weak
    if strength == 5:
        print("Password is strong")
    elif 3 <= strength <= 4:
        print("Password is fair, recommend including ")
        for req in missing_requirements:
            print(f" - {req}")
    else:
        print("Password is weak, recommend including ")
        for req in missing_requirements:
            print(f" - {req}")
    
def main():
    password = getpass.getpass("Enter your password: ")
    check_password(password)      
        
if __name__ == "__main__":
    main()