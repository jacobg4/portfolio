#Task 2: Log File Analyzer
#Objective: Build a script that analyzes a web server log (.log file) to extract key data like IP addresses, timestamps, and HTTP status codes.
#Requirements:

#Read the .log file line by line.
#Extract unique IP addresses and count how many times they appear.
#Identify the most common HTTP status codes.
#Suggested Libraries:

#re (for regular expression parsing)
#collections (for efficient counting)

import re
import os
from collections import Counter

ip_pattern = r'\b(?:\d{1,3}\.){3}\d{1,3}\b'
status_code_pattern = r'"\s*(\d{3})\s'   # Matches HTTP status codes more reliably

ip_counter = Counter()
status_code_counter = Counter()


def main():
    total_requests = 0
    if not os.path.exists("sample.log"):
        print("Error: sample.log not found. Please check the file path.")
        return
    with open("sample.log") as f:
        for line in f:
            if not line.strip() or line.startswith("#"):
                continue  # Skip blank or comment lines
            total_requests += 1
            ip_match = re.search(ip_pattern, line)
            status_match = re.search(status_code_pattern, line)
        
            if ip_match:
                ip_counter[ip_match.group()] += 1
        
            if status_match:
                status_code_counter[status_match.group()] += 1
    print("Top 5 IP Addresses:")
    for ip, count in ip_counter.most_common(5):
        print(f"{ip}: {count} requests")

    print("\nTop 5 Status Codes:")
    for code, count in status_code_counter.most_common(5):
        print(f"{code}: {count} occurrences")
        
    print(f"\nTotal Requests Processed: {total_requests}")

    
    
    
    
if __name__ == "__main__":
    main()