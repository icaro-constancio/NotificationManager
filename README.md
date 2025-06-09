# NotificationManager for Discord and Email
This C++ project allows sending messages to a **Discord channel via webhook** and **emails via STMP** through a terminal menu. I chose to use environment variables to load credentials (sender, recipient, app password, and webhook URL).


## Requirements 
- C++ compiler
- Libcurl
- Visual Studio

### 1. Installing `libcurl`:

```
sudo apt install libcurl4-openssl-dev
```
## 2. Setting Environment Variables:
To configure environment variables, I added the lines below to the `profile` file. This allows the credentials to load automatically every time I use the program, without needing to reconfigure them.

**Important: You must use an app password(not your personal account password) for SMTP connections. I generated mine at: https://myaccount.google.com/apppasswords**

To open the file in the terminal: 

```
code ~/.profile
```

Then, at the end of the file, add:

```
export USER_EMAIL="replace_with_your_email"
export USER_PASSWORD="replace_with_your_app_password"
export RECIPIENT_EMAIL="replace_with_recipient_email"
export DISCORD_WEBHOOK="replace_with_discord_webhook_url"
```

To apply the changes in the current session:
```
source ~/.profile
```

## 3. Compiling the Code
If you don't have `g++` installed:

```
sudo apt install build-essential
```
To compile the program:

```
g++ -o notify NotificationManager.cpp -lcurl

```

To run: 

```
./notify

```
