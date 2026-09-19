#Task 1: File Cleanup Automation
#Objective: Write a script that organizes files in a folder based on their type (e.g., .txt, .jpg, .pdf, etc.).
#Requirements:

#Scan a specified directory.
#Create folders based on file types.
#Move files into the appropriate folders.

import os
import shutil
import pathlib

# Open src directory
def get_src_dr():
    src_dr = input("Enter source directory file path.").strip()    #Takes user input for their source directory
    if not os.path.exists(src_dr):
        print("Error: source directory not found")
        return None
    if os.path.isdir(src_dr):
        return src_dr
    else:
        print("Error: source is not a directory")
        return

#Checks for existance of target directory, creates directory if not found
def get_tar_dr(src_dr, ext):
    target_path = os.path.join(src_dr, ext)
    if not os.path.exists(target_path):
        os.mkdir(target_path)
    return target_path

#Creates unique filenames to prevent overwriting
def generate_unique_filename(destination_path):
    base, ext = os.path.splitext(destination_path)
    counter = 1
    while os.path.exists(destination_path):
        destination_path = f"{base}_{counter}{ext}"
        counter += 1
    return destination_path

# Get src file if file type == existing destination_dr copy file to directory else create new dr and copy file

def main():
    src_dr = get_src_dr()
    if not src_dr:
        return
    for entry in os.scandir(src_dr):
        if entry.is_file():
            ext = os.path.splitext(entry.name)[1].strip('.') or "Unknown"    #Files with no extension are grouped into Unknown
            tar_dr = get_tar_dr(src_dr, ext)
            destination_path = generate_unique_filename(os.path.join(tar_dr, entry.name))
            shutil.move(entry.path, destination_path)
            print(f"Moved '{entry.name}' to '{tar_dr}'")  #Could edit to print to a log file

        else:
            print(f"Could not move {entry.name}, {entry.name} is not a file.")

if __name__ == "__main__":
    main()


