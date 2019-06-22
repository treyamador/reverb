#include "core.h"
#include "wav_manager.h"
#include "wav.h"

Core::Core() {

}

Core::~Core() {

}

void Core::run() {
    WAVManager manager;
    // manager.add_wav("files/Balam Acab - Apart.wav");
    // WAV* wav = manager["files/Balam Acab - Apart.wav"];
    // "Hiroshi_Yoshimura_-_View_From_My_Window.wav"
    manager.add_wav("files/Hiroshi_Yoshimura_-_View_From_My_Window.wav");
    WAV* wav = manager["files/Hiroshi_Yoshimura_-_View_From_My_Window.wav"];
    std::cout << wav << std::endl;
    manager.write_wav(wav, "files/out.wav");
}
