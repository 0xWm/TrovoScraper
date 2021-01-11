# Trovo Follower Scraper 

Get a list of followers from broadcasters channel

## Getting Started

### In order to start this you need:

Server:
1. Python 3 (used python 3.8.5)

Client:
1. Unreal Engine 4.25 (used Unreal Engine 4.25.4)
2. Visual Studio Code for compilation, or IDE of your choice (Used VSCodium on Linux)
If using any other IDE then you have to regenerate project files as there is only Visual Studio Code compatible project file.

If want to use client only you need to send json to URL and Port (which will be 127.0.0.1:8080/ by default)
json must contain this data
```yaml
{
  "params": {
    "broadcaster_name": name_of_broadcaster_here,
    "follower_count": count_here_300_for_example
  }
}
```

## Description
My friend is streaming using Trovo service (website: https://trovo.live) and he is also making games using Unreal Engine 4. He manually input random follower name into a text box which is displayed while he is playing the game he made. He didn't have time to automate this, so naturally i automated this process. But Trovo does not have any kind of API to get follower list, hence the scruber.  

### Making It Run

executing file main.py will run server on 127.0.0.1:8080/

inside Unreal Engine project edit function arguments inside "InitServerData". ServerURL and Port must match the URL and Port from the server. 
Input broadcaster name, which is empty for now
Input Followe Count, and make sure it is less then current followers broadcaster has. I did not test with number above current folowers count and have no idea what will happend

If you get everything right this is the outcome:
[![Watch the video](https://img.youtube.com/vi/dMSLNR9mPzs/maxresdefault.jpg)](https://youtu.be/dMSLNR9mPzs)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE) file for details
