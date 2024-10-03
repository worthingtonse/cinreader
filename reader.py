from enum import Enum
from typing import List, Optional, Union
import sys

class MessageType(Enum):
    INT_INVALID = 0
    INT_OUT_OF_RANGE = 1
    STRING_CANNOT_BE_EMPTY = 2
    CHAR_NOT_ALLOWED = 3
    DOUBLE_INVALID = 4
    FLOAT_INVALID = 5
    BOOL_INVALID = 6
    STRING_NOT_ALLOWED = 7
    INT_TOO_LARGE = 8

class CinReader:
    def __init__(self):
        self.messages = {
            MessageType.INT_INVALID: "Input is not a valid integer. Re-enter: ",
            MessageType.FLOAT_INVALID: "Input is not a valid float. Re-enter: ",
            MessageType.DOUBLE_INVALID: "Input is not a valid double. Re-enter: ",
            MessageType.INT_OUT_OF_RANGE: "Input is not in the required range. Re-enter: ",
            MessageType.STRING_CANNOT_BE_EMPTY: "Input cannot be empty. Re-enter: ",
            MessageType.CHAR_NOT_ALLOWED: "Input character is not allowed. Re-enter: ",
            MessageType.BOOL_INVALID: "Input is not valid for boolean. Re-enter: ",
            MessageType.STRING_NOT_ALLOWED: "Input is not allowed. Re-enter: ",
            MessageType.INT_TOO_LARGE: "Input is too large, Re-enter: "
        }

    def read_bool(self) -> bool:
        while True:
            try:
                user_input = self.read_string(allow_empty=False).upper()
                if user_input.startswith('T'):
                    return True
                elif user_input.startswith('F'):
                    return False
                else:
                    print(self.messages[MessageType.BOOL_INVALID], end='')
            except (EOFError, KeyboardInterrupt):
                sys.exit()

    def read_char(self, allowed: str = "") -> str:
        while True:
            try:
                char = self.read_string(allow_empty=False)[0]
                if not allowed or char in allowed:
                    return char
                print(self.messages[MessageType.CHAR_NOT_ALLOWED], end='')
            except (EOFError, KeyboardInterrupt):
                sys.exit()

    def read_double(self) -> float:
        while True:
            try:
                return float(self.read_string(allow_empty=False))
            except ValueError:
                print(self.messages[MessageType.DOUBLE_INVALID], end='')
            except (EOFError, KeyboardInterrupt):
                sys.exit()

    def read_float(self) -> float:
        return self.read_double()

    def read_int(self, min_val: int = -sys.maxsize - 1, max_val: int = sys.maxsize) -> int:
        while True:
            try:
                int_str = self.read_string(allow_empty=False)
                if len(int_str) > 9:
                    print(self.messages[MessageType.INT_TOO_LARGE], end='')
                    continue
                value = int(int_str)
                if min_val <= value <= max_val:
                    return value
                print(self.messages[MessageType.INT_OUT_OF_RANGE], end='')
            except ValueError:
                print(self.messages[MessageType.INT_INVALID], end='')
            except (EOFError, KeyboardInterrupt):
                sys.exit()

    def read_string(self, allow_empty: bool = True) -> str:
        while True:
            try:
                user_input = input()
                if not allow_empty and not user_input:
                    print(self.messages[MessageType.STRING_CANNOT_BE_EMPTY], end='')
                    continue
                return user_input
            except (EOFError, KeyboardInterrupt):
                sys.exit()

    def read_string_from_list(self, allowed_strings: List[str], case_sensitive: bool = True) -> str:
        allowed = allowed_strings if case_sensitive else [s.upper() for s in allowed_strings]
        
        while True:
            user_input = self.read_string()
            check_input = user_input if case_sensitive else user_input.upper()
            
            if check_input in allowed:
                return user_input
            print(self.messages[MessageType.STRING_NOT_ALLOWED], end='')

    def set_message(self, message_type: MessageType, message: str):
        if message_type in MessageType:
            self.messages[message_type] = message

# Example usage:
if __name__ == "__main__":
    reader = CinReader()
    
    # Examples of how to use the CinReader
    print("Enter a boolean (T/F):", end=' ')
    bool_val = reader.read_bool()
    print(f"You entered: {bool_val}")
    
    print("Enter an integer between 1 and 10:", end=' ')
    int_val = reader.read_int(1, 10)
    print(f"You entered: {int_val}")
    
    print("Enter a float:", end=' ')
    float_val = reader.read_float()
    print(f"You entered: {float_val}")
    
    print("Enter a string (from 'yes', 'no', 'maybe'):", end=' ')
    str_val = reader.read_string_from_list(['yes', 'no', 'maybe'])
    print(f"You entered: {str_val}")
