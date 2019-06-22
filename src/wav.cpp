#include "wav.h"


namespace {
	static const int BUF_SIZE = 4;
}


WAV::WAV() {
	header_ = new Header;
	header_->riff_tag_ = new char[BUF_SIZE + 1];
	header_->riff_tag_[BUF_SIZE] = '\0';
	header_->riff_length_ = new int;
	header_->wav_tag_ = new char[BUF_SIZE + 1];
	header_->wav_tag_[BUF_SIZE] = '\0';
	header_->fmt_tag_ = new char[BUF_SIZE + 1];
	header_->fmt_tag_[BUF_SIZE] = '\0';
	header_->fmt_length_ = new int;
	header_->audio_format_ = new short;
	header_->num_channels_ = new short;
	header_->sample_rate_ = new int;
	header_->byte_rate_ = new int;
	header_->block_align_ = new short;
	header_->bits_per_sample_ = new short;
	header_->data_tag_ = new char[BUF_SIZE + 1];
	header_->data_tag_[BUF_SIZE] = '\0';
	header_->data_length_ = new int;
	body_ = new Body;
}


WAV::~WAV() {
	delete [] header_->riff_tag_;
	delete header_->riff_length_;
	delete [] header_->wav_tag_;
	delete [] header_->fmt_tag_;
	delete header_->fmt_length_;
	delete header_->audio_format_;
	delete header_->num_channels_;
	delete header_->sample_rate_;
	delete header_->byte_rate_;
	delete header_->block_align_;
	delete header_->bits_per_sample_;
	delete [] header_->data_tag_;
	delete header_->data_length_;
	delete header_;
	delete[] body_->data_;
	delete body_;
}


std::ostream& operator<<(std::ostream& stream, WAV* wav) {
	stream << "Riff tag         " << wav->header_->riff_tag_ << "\n";
	stream << "Riff length      " << *wav->header_->riff_length_ << "\n";
	stream << "WAV tag          " << wav->header_->wav_tag_ << "\n";
	stream << "Format tag       " << wav->header_->fmt_tag_ << "\n";
	stream << "Format length    " << *wav->header_->fmt_length_ << "\n";
	stream << "Audio format     " << *wav->header_->audio_format_ << "\n";
	stream << "Number channels  " << *wav->header_->num_channels_ << "\n";
	stream << "Sample rate      " << *wav->header_->sample_rate_ << "\n";
	stream << "Byte rate        " << *wav->header_->byte_rate_ << "\n";
	stream << "Block align      " << *wav->header_->block_align_ << "\n";
	stream << "Bits per sample  " << *wav->header_->bits_per_sample_ << "\n";
	stream << "Data tag         " << wav->header_->data_tag_ << "\n";
	stream << "Data length      " << *wav->header_->data_length_ << "\n";
	return stream;
}

