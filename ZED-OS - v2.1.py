import os, time, getpass, urllib.parse
VERSION="2.1 INTERNET [CURL] FINAL"
AUTHOR="invisibleman31coder"
G="\033[92m"; C="\033[96m"; R="\033[91m"; Y="\033[93m"; W="\033[0m"
os.system("clear")
print(f"{C}███████╗███████╗██████╗       ██████╗ ███████╗{W}")
print(f"{C}╚══███╔╝██╔════╝██╔══██╗     ██╔═══██╗██╔════╝{W}")
print(f"{C}  ███╔╝ █████╗  ██║  ██║     ██║   ██║███████╗{W}")
print(f"{C} ███╔╝  ██╔══╝  ██║  ██║     ██║   ██║╚════██║{W}")
print(f"{C}███████╗███████╗██████╔╝     ╚██████╔╝███████║{W}")
print(f"{C}╚══════╝╚══════╝╚═════╝       ╚═════╝ ╚══════╝{W}")
print(f"{Y}           v{VERSION}\n           Author: {AUTHOR}\n")
for i in [0,40,80,100]:
    print(f"{G}[{i}%] Connecting to ZED-NET...{W}"); time.sleep(0.2)
pwd=getpass.getpass(f"{C}Password: {W}")
print(f"{G}Access Granted. Welcome {AUTHOR}{W}\n")
while True:
    cmd=input(f"{G}ZED-OS {VERSION} | {AUTHOR}$ {W}").strip()
    if cmd=="exit": break
    elif cmd=="ip": os.system("curl -s https://api.ipify.org; echo")
    elif cmd=="weather": os.system("curl -s wttr.in/Durban?format=3; echo")
    elif cmd.startswith("browser "):
        q=cmd[8:].replace(" ","+")
        print(f"{Y}Results:{W}")
        os.system(f"curl -s -A 'Mozilla/5.0' 'https://lite.duckduckgo.com/lite/?q={q}' | grep -o 'uddg=[^\"]*' | sed 's/uddg=//;s/%2F/\\//g;s/%3A/:/g;s/%2E/./g' | cut -d'&' -f1 | head -10")
    elif cmd=="help": print("ip, weather, browser <query>, exit")
    else: print("Unknown")
