#pragma once

#include "ofMain.h"
#include "ofxAndroid.h"
#include "ofxImageSequence.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"

/*
#define HOST1 "192.168.1.16"
#define HOST2 "192.168.1.47"
#define HOST3 "192.168.1.13"
*/
#define HOST1 "192.168.1.15"
#define HOST2 "192.168.1.11"
#define HOST3 "192.168.1.24"
#define HOST4 "192.168.1.17"

#define SEQIP "192.168.1.28"

#define RCVPORT 9999
#define CTLPORT 9998
#define SEQPORT 9393

class ofApp : public ofxAndroidApp{
		void setup();
		void update();
		void draw();

		void touchDown(int x, int y, int id);
		void touchMoved(int x, int y, int id);
		void touchUp(int x, int y, int id);
		/*
		void touchDoubleTap(int x, int y, int id);
		void touchCancelled(int x, int y, int id);
		void swipe(ofxAndroidSwipeDir swipeDir, int id);

		void pause();
		void stop();
		void resume();
		void reloadTextures();

		bool backPressed();
		void okPressed();
	   	void cancelPressed();
        */

        void switchMedia(int wich);
	    void remapSel(int vidW, int vidH);

        ofPlanePrimitive  videoProjections[4];

        vector<ofxImageSequence> images;

        int grid_res, vWidth, vHeight, spacer, slice, spacer2, spliceH;
        int sliceW, sliceH;
        ofPoint previewScreens[3];
        ofRectangle selections[4];
        ofRectangle m_selections[4];
        int vidMap[4];
        ofRectangle sliceZone, changeZone, animZone, mapZone, dev1, dev2, dev3, dev4;
        bool mapMode;
        int maxSel, wichVid, wichSel;

        bool selecting, drawVid, loading;

        ofDirectory media;

        ofxOscSender ctlz[4];
        ofxOscSender seq;

        string labels[3];

        ofPoint velo[4];
        bool animate;

        ofxOscReceiver receiver;
        int numLoaded;
        string loadPath, destLoadPath;
        void loadMedia(string path, int numFiles);
        void sendWich2Load(int dest, string path, int numFiles);
        vector<string> fileNames;
        void getNumFilesInDir(string dir);

        //ORGANISE STUFFS HERE

        //GUI
        unsigned int mode2show;
        ofImage bgImage;
        ofTrueTypeFont wallFont;
        ofTrueTypeFont wallFontSmall;

        ofRectangle channelsButtons[3];
        ofRectangle playChanButtons;
        ofRectangle stopChanButtons;
        string channelsNames[3];

        ofImage previewImgs[3];
        bool previewLoaded;

        ofRectangle changeMode;

        //settings from XML
        void loadChannelFromXml();
        void switchChannels(string channel_Name);

        string seqPath;

        //SEND CHANNELS OSC
        void sendChannelOSC(string channel_Name);
        void sendClear();
        void sendStartSequence();
        void sendStopSequence();
        void sendLoadSequence(unsigned int sequence);



};
