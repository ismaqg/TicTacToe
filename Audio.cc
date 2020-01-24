#include "Audio.hh"

Audio::Audio(string file, float initial_volume){
    volume_factor = initial_volume / 10.0f;
    volume = initial_volume;
    if(not sound.openFromFile(file)) cerr << "ERROR opening " << file << endl;
    sound.setVolume(initial_volume);
    muted = false;
}

void Audio::Play(bool setloop){
    sound.play();
    sound.setLoop(setloop);
}

void Audio::Pause(){
    sound.pause();
}

void Audio::Stop(){
    sound.stop();
}

void Audio::Mute_or_unmute(){
    if(muted){ //si está muteada, desmuteamos
        sound.setVolume(volume);
        muted = false;
    } 
        
    else{
        sound.setVolume(0.0f);
        muted = true;
    }
         
}

void Audio::Volume_up(){
    if(muted){
        volume = volume_factor; //volume = 0 (esta muteada) + volume_factor;
        sound.setVolume(volume);
        muted = false;
    }
    else{
        volume += volume_factor;
        sound.setVolume(volume);
    }
}

void Audio::Volume_down(){
    if(sound.getVolume() != 0.0f){
        volume -= volume_factor;
        if(volume < 0.0f) volume = 0.0f; //creo que no deberia pasar nunca porque el volumen factor es un valor del cual el volumen es multiplo. Pero mejor curarnos en salud...
        sound.setVolume(volume);
    }
}
