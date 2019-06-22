#include <algorithm>
#include "wav_manager.h"
#include "reader_writer.h"
#include "wav.h"


namespace {
	const int DEFAULT_HEADER_SIZE = 44;
	const int TAG_SIZE = 4;

	const float BYTES_PER_BIT = 1.0f / 8.0f;
	const float SECONDS_PER_MINUTE = 60.0f / 1.0f;
}


WAVManager::WAVManager() :
	reader_writer_(std::make_shared<ReaderWriter>())
{}


WAVManager::~WAVManager() {
	clear_wav_files();
	reader_writer_.reset();
}


WAV* WAVManager::add_wav(const std::string& filepath) {
	if (!wav_files_.count(filepath))
		wav_files_[filepath] = reader_writer_->read(filepath);
	return wav_files_[filepath];
}


void WAVManager::write_wav(WAV* wav, const std::string& filepath) {
	reader_writer_->write(wav, filepath);
}


void WAVManager::delete_wav(const std::string& key) {
	wav_files_.erase(key);
}


void WAVManager::clear_wav_files() {
	for (auto iter = wav_files_.begin(); iter != wav_files_.end(); ++iter) {
		if (iter->second != nullptr) {
			delete iter->second;
			iter->second = nullptr;
		}
	}
	wav_files_.clear();
}


WAV* WAVManager::create_empty_given_format(WAV* prototype) {
	WAV* wav = new WAV;
	copy_tag(wav->header_->riff_tag_, prototype->header_->riff_tag_);
	copy_tag(wav->header_->wav_tag_, prototype->header_->wav_tag_);
	copy_tag(wav->header_->fmt_tag_, prototype->header_->fmt_tag_);
	copy_tag(wav->header_->data_tag_, prototype->header_->data_tag_);
	*wav->header_->fmt_length_ = *prototype->header_->fmt_length_;
	*wav->header_->audio_format_ = *prototype->header_->audio_format_;
	*wav->header_->num_channels_ = *prototype->header_->num_channels_;
	*wav->header_->sample_rate_ = *prototype->header_->sample_rate_;
	*wav->header_->byte_rate_ = *prototype->header_->byte_rate_;
	*wav->header_->block_align_ = *prototype->header_->block_align_;
	*wav->header_->bits_per_sample_ = *prototype->header_->bits_per_sample_;
	*wav->header_->riff_length_ = 0;
	*wav->header_->data_length_ = 0;
	wav->body_->data_ = nullptr;
	return wav;
}


void WAVManager::set_size(WAV* unsized, int num_bytes) {
	*unsized->header_->data_length_ = num_bytes;
	*unsized->header_->riff_length_ = num_bytes + DEFAULT_HEADER_SIZE - 8;
	unsized->body_->data_ = new char[num_bytes + 1];
	unsized->body_->data_[num_bytes] = '\0';
	for (int i = 0; i < num_bytes; ++i)
		unsized->body_->data_[i] = 0;
}


WAV* WAVManager::create_sized_given_format(WAV* prototype, int size) {
	WAV* new_wav = create_empty_given_format(prototype);
	set_size(new_wav, size);
	return new_wav;
}


void WAVManager::copy_tag(char*& dest, char* source) {
	for (int i = 0; i < TAG_SIZE; ++i)
		dest[i] = source[i];
}


int WAVManager::largest_data_size(std::vector<WAV*>& channels) {
	auto iter = channels.begin();
	int largest = *(*iter)->header_->data_length_;
	++iter;
	while (iter != channels.end()) {
		int comparison = *(*iter)->header_->data_length_;
		if (comparison > largest)
			largest = comparison;
		++iter;
	}
	return largest;
}


WAV* WAVManager::operator[](int k) {
	std::vector<std::string> keys = query_keys();
	std::sort(keys.begin(), keys.end());
	return wav_files_[keys[k]];
}


WAV* WAVManager::operator[](const std::string& key) {
	return wav_files_[key];
}


std::vector<std::string> WAVManager::query_keys() {
	std::vector<std::string> keys;
	for (auto iter = wav_files_.begin(); iter != wav_files_.end(); ++iter)
		keys.push_back(iter->first);
	return keys;
}


size_t WAVManager::size() {
	return wav_files_.size();
}

