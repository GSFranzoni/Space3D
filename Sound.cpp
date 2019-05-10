#include "Sound.h"

Sound::Sound(string url){
    this->buffer.loadFromFile(url);
    this->sound.setBuffer(buffer);
}

void Sound::play(int volume){
    this->sound.setVolume(volume);
    this->sound.play();
}

void Sound::playLoop(int volume){
    this->sound.setVolume(volume);
    this->sound.setLoop(true);
    this->sound.play();
}

void Sound::stop(){
    this->sound.stop();
}
