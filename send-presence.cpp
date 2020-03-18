#include <iostream>
#include "discord_rpc.h"
#include <cstring>

using namespace std;

static char APPLICATION_ID[19] = {0};
static bool SendPresence = true;

static void updateDiscordPresence(char* details, char* state, char* largeImageKey, char* smallImageKey)
{
    if (SendPresence) {
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

static void discordInit()
{
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    handlers.ready = handleDiscordReady;
    handlers.disconnected = handleDiscordDisconnected;
    handlers.errored = handleDiscordError;
    Discord_Initialize(APPLICATION_ID, &handlers, 1, NULL);
}

static void inputLoop()
{
    SendPresence = true;
    printf("Rich presence loop begins\n");

    while (SendPresence) {
        cin.clear();
        cin.sync();

        // the 128 character limit is made up by me
        char details[128] = {0};
        char state[128] = {0};
        char largeImageKey[128] = {0};
        char smallImageKey[128] = {0};

        cout << "Details: ";
        cin.getline(details, sizeof(details));
        if (details[0] == 0) {
            Discord_ClearPresence();
            continue;
        }

        cout << "State: ";
        cin.getline(state, sizeof(state));
        if (state[0] == 0) {
            Discord_ClearPresence();
            continue;
        }

        cout << "Large Image Key: ";
        cin.getline(largeImageKey, sizeof(largeImageKey));
        if (largeImageKey[0] == 0) {
            Discord_ClearPresence();
            continue;
        }

        cout << "Small Image Key: ";
        cin.getline(smallImageKey, sizeof(smallImageKey));
        if (smallImageKey[0] == 0) {
            Discord_ClearPresence();
            continue;
        }

        updateDiscordPresence(details, state, largeImageKey, smallImageKey);
        cout << "\nSent to discord!\n";
    }
}


int main(int argc, char* argv[])
{
    cin.clear();
    cin.sync();
    // Collect application id from stdin
    cout << "Application ID: ";
    cin.getline(APPLICATION_ID, sizeof(APPLICATION_ID));

    // Initialize communications with Discord
    discordInit();

    // Start our input loop
    inputLoop();

    // Clean shutdown
    Discord_Shutdown();
    
    return 0;
}
