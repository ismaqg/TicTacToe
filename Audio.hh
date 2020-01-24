#include <SFML/Audio.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Audio{
    public:
        Audio(string file, float initial_volume);

        void Play(bool setloop);
        void Pause();
        void Stop();
        void Mute_or_unmute();
        void Volume_up();
        void Volume_down();

    private:
        float volume;
        float volume_factor; //sera la cantidad de volumen que subamos o bajemos en cada subir volumen
        Music sound;
        bool muted;
};