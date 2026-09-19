#Task 4 Network Scanning
#Core Objectives
#Your network scanner should:

#Accept a target IP address or IP range (e.g., 192.168.1.0/24).
#Scan for active hosts.
#Check for open ports on discovered hosts.
#Display results with clear feedback.

import ipaddress
import socket
import subprocess

common_ports = [22, 80, 443, 8080]
def get_hostip():
    ip = socket.gethostbyname(input('Input host name: '))
    print(f"IP Address for example.com: {ip}")
    return ip
    
def get_ip():
    ip = input("Input IP address or IP range: ").strip()
    try:
        if '/' in ip:
            ipaddress.IPv4Network(ip, strict=False)  # Subnet check
        else:
            ipaddress.IPv4Address(ip)  # Single IP check
        return ip
    except ValueError:
        print("Error: Invalid IP address or range.")
        return None
        
def scan_port(ip, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.settimeout(1)  # Avoid slow scans
    result = sock.connect_ex((ip, port))  
    if result == 0:
        print(f"[+] Port {port} is OPEN on {ip}")
    else:
        print(f"[-] Port {port} is CLOSED on {ip}")
    sock.close()

def is_host_alive(ip):
    try:
        subprocess.run(["ping", "-n", "1", "-w", "500", ip], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        return True
    except subprocess.CalledProcessError:
        return False
        
def main():
    command = int(input("[1] Get IP by hostname. [2] Input IP or subnet directly: "))
    if command == 1:
        ip = get_hostip()
    elif command == 2:
        ip = get_ip()
    else:
        print("Invalid Command, goodbye...")
        return
    if not ip:
        ip = get_ip()
    elif '/' in ip:
        for ip in ipaddress.IPv4Network(ip, strict=False):
            ip_str = str(ip)  # Convert IPv4Address object to string
            if is_host_alive(ip_str):
                print(ip_str)
                for port in common_ports:
                    scan_port(ip_str, port)
            else:
                print(f"Host at {ip_str} is not alive")
    else:
        print(ip)
        if is_host_alive(ip):
            for port in common_ports:
                scan_port(ip, port)
        else:
            print(f"Host at {ip} is not alive")

if __name__ == "__main__":
    main()        