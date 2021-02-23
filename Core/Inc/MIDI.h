/*
 * MIDI.h
 *
 *  Created on: Jan 12, 2021
 *      Author: thomas
 */

#ifndef MIDI_H_
#define MIDI_H_


#ifdef __cplusplus
extern "C" {
#endif


void Midi_process();
void data_parse();

#ifdef __cplusplus
}
#endif
/* 1st byte (status) */
//#define NOTES_OFF_MIN 0x80
//#define NOTES_OFF_MAX 0x8F
//
//#define NOTES_ON_MIN 0x90
//#define NOTES_ON_MAX 0x9F
//
//#define POLYPHONIC_AFTERTOUCH_MIN 0xA0
//#define POLYPHONIC_AFTERTOUCH_MAX 0xAF
//
//#define CONTROL_MODE_CHANGE_MIN 0xB0
//#define CONTROL_MODE_CHANGE_MAX 0xBF
//
//#define PROGRAM_CHANGE_MIN 0xC0
//#define PROGRAM_CHANGE_MAX 0xCF
//
//#define CHANNEL_AFTERTOUCH_MIN 0xD0
//#define CHANNEL_AFTERTOUCH_MAX 0xDF
//
//#define PITCH_WHEEL_RANGE_MIN 0xE0
//#define pITCH_WHEEL_RANGE_MAX 0xEF
//
//#define SYSTEM_EXCLUSIVE 0xF0


//#define SONG_POSITION_POINTER 0xF2

/* 2nd byte (data1) */
#endif /* MIDI_H_ */
