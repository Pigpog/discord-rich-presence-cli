#include <iostream>
#include "discord_rpc.h"
#include <cstring>

using namespace std;


static const char* APPLICATION_ID = "410664151334256663";
static int SendPresence = 1;

static void updateDiscordPresence(char* details, char* state, char* largeImageKey, char* smallImageKey)
{
    if (SendPresence) {
        char buffer[256];
        DiscordRichPresence discordPresence;
        memset(&discordPresence, 0, sizeof(discordPresence));
        discordPresence.state = state;
        discordPresence.details = details;
        //discordPresence.startTimestamp = StartTime;
        //discordPresence.endTimestamp = time(0) + 5 * 60;
        discordPresence.largeImageKey = largeImageKey;
        discordPresence.smallImageKey = smallImageKey;
        discordPresence.instance = 0;
        Discord_UpdatePresence(&discordPresence);
    }
    else {
        Discord_ClearPresence();
    }
}

static void handleDiscordReady(const DiscordUser* connectedUser)
{
    printf("\nDiscord: connected to user %s#%s - %s\n",
           connectedUser->username,
           connectedUser->discriminator,
           connectedUser->userId);
}

static void handleDiscordDisconnected(int errcode, const char* message)
{
    printf("\nDiscord: disconnected (%d: %s)\n", errcode, message);
}

static void handleDiscordError(int errcode, const char* message)
{
    printf("\nDiscord: error (%d: %s)\n", errcode, message);
}

static void handleDiscordJoin(const char* secret)
{
    printf("\nDiscord: join (%s)\n", secret);
}

static void handleDiscordSpectate(const char* secret)
{
    printf("\nDiscord: spectate (%s)\n", secret);
}

static void handleDiscordJoinRequest(const DiscordUser* request)
{
   
}

static void discordInit()
{
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    handlers.ready = handleDiscordReady;
    handlers.disconnected = handleDiscordDisconnected;
    handlers.errored = handleDiscordError;
    handlers.joinGame = handleDiscordJoin;
    handlers.spectateGame = handleDiscordSpectate;
    handlers.joinRequest = handleDiscordJoinRequest;
    Discord_Initialize(APPLICATION_ID, &handlers, 1, NULL);
}

static void inputLoop()
{
    SendPresence = 1;
    char line[512];
    char* space;

    printf("Rich presence loop begins\n");
    while (SendPresence) {
        cin.clear();
        cin.sync();
        char details[128];
        char state[128];
        char largeImageKey[128];
        char smallImageKey[128];

        cout << "Details: ";
        cin.getline(details, sizeof(details));
        cout << "State: ";
        cin.getline(state, sizeof(state));
        cout << "Large Image Key: ";
        cin.getline(largeImageKey, sizeof(largeImageKey));
        cout << "Small Image Key: ";
        cin.getline(smallImageKey, sizeof(smallImageKey));

        cout << "\nSent to discord!\n";
    
        updateDiscordPresence(details, state, largeImageKey, smallImageKey);
    }
    Discord_Shutdown();
}


int main(int argc, char* argv[])
{
    discordInit();

    inputLoop();
    
    return 0;
}
