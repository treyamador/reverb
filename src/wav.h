#ifndef WAV_H_
#define WAV_H_
#include <iostream>

struct WAV {
    struct Header {
        char* riff_tag_;
        int* riff_length_;
        char* wav_tag_;
        char* fmt_tag_;
        int* fmt_length_;
        short* audio_format_;
        short* num_channels_;
        int* sample_rate_;
        int* byte_rate_;
        short* block_align_;
        short* bits_per_sample_;
        char* data_tag_;
        int* data_length_;
    } *header_;
    struct Body {
        char* data_;
    } *body_;

    WAV();
    ~WAV();

    friend std::ostream& operator<<(std::ostream& stream, WAV* wav);
};

#endif
