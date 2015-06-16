#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_NOTICE);
    ofBackground(255);
    //ofSetWindowPosition(0, 0);
    //ofSetFrameRate(30);
    ofEnableAlphaBlending();
    ofEnableArbTex();

    //media.listDir("media");

    wichSel = 0;
    wichVid = 0;
    maxSel = 4;
    selecting = false;
    loading = false;
    drawVid = true;

    sliceW = 640;
    sliceH = 480;

    sliceZone.x = 0;
    sliceZone.y = 0;
    sliceZone.width = sliceW;
    sliceZone.height = sliceH;

    changeZone.x = 0;
    changeZone.y = 500;
    changeZone.width = 175;
    changeZone.height = 100;

    mapZone.x = 177;
    mapZone.y = 500;
    mapZone.width = 175;
    mapZone.height = 100;

    animZone.x = 0;
    animZone.y = 610;
    animZone.width = 350;
    animZone.height = 100;

    //preview setup

        previewScreens[0].x = 240;
        previewScreens[0].y = 135;

        previewScreens[1].x = 220;
        previewScreens[1].y = 115;

        previewScreens[2].x = 200;
        previewScreens[2].y = 95;

    //13"
        videoProjections[0].set(previewScreens[0].x,  previewScreens[0].y);
        videoProjections[0].setPosition(800, 150, 0);
        videoProjections[0].setResolution(8, 8);
        //10"
        videoProjections[1].set(previewScreens[1].x,  previewScreens[1].y);
        videoProjections[1].setPosition(800, 310, 0);
        videoProjections[1].setResolution(8, 8);
        //10"
        videoProjections[2].set(previewScreens[1].x,  previewScreens[1].y);
        videoProjections[2].setPosition(1100, 310, 0);
        videoProjections[2].setResolution(8, 8);
        //8"
        videoProjections[3].set(previewScreens[2].x, previewScreens[2].y);
        videoProjections[3].setPosition(800, 500, 0);
        videoProjections[3].setResolution(8, 8);

        dev1.x = 800 - (previewScreens[0].x/2);
        dev1.y= 150 - (previewScreens[0].y/2);
        dev1.width = 240;
        dev1.height = 135;

        dev2.x = 800 - (previewScreens[1].x/2);
        dev2.y= 310 - (previewScreens[1].y/2);
        dev2.width = 220;
        dev2.height = 115;

        dev3.x = 1100 - (previewScreens[1].x/2);
        dev3.y= 310 - (previewScreens[1].y/2);
        dev3.width = 220;
        dev3.height = 115;

        dev4.x = 800 - (previewScreens[2].x/2);
        dev4.y = 500 - (previewScreens[2].y/2);
        dev4.width = 200;
        dev4.height = 95;


    /*
    videoProjections[0].set(480,  270);
    videoProjections[0].setPosition(1000, 150, 0);
    videoProjections[0].setResolution(8, 8);

    videoProjections[1].set(270,  480);
    videoProjections[1].setPosition(1000, 530, 0);
    videoProjections[1].setResolution(8, 8);

    videoProjections[2].set(480,  270);
    videoProjections[2].setPosition(620, 635, 0);
    videoProjections[2].setResolution(8, 8);
    */

    for(int i = 0; i<maxSel;i++){

        selections[i].x =0;
        selections[i].y = 0;
        selections[i].width = sliceW;
        selections[i].height = sliceH;
    }


    //osc stuff
    ctlz[0].setup(HOST1, RCVPORT);
    ctlz[1].setup(HOST2, RCVPORT);
    ctlz[2].setup(HOST3, RCVPORT);
    ctlz[3].setup(HOST4, RCVPORT);

    for(int i = 0; i<3;i++){

        velo[i].x = ofRandom(-0.1, 0.1);
        velo[i].y = ofRandom(-0.1, 0.1);

    }
    for(int i = 0; i<3;i++){
        vidMap[i] = wichVid;
    }

    labels[0] = "CH";
    labels[1] = "MAP";
    labels[2] = "ANIM";
    ofLog(OF_LOG_NOTICE, "setting up OSC");
    receiver.setup(RCVPORT);

    destLoadPath = "/storage/emulated/0/wall_box/";
    //destLoadPath = "/mnt/sd_card/wall_box/";
    loadPath = "/sdcard/wall_box/";
    seqPath = "/home/ekko/wall_box/Dropbox/wall_box/";

    numLoaded = 0;
    ofLog(OF_LOG_NOTICE, "done setting up OSC");

    //ORGANISE STUFF HERE
    //backgroung and text infos
    bgImage.loadImage("bckgrImgWhite.png");
    mode2show = 0;
    wallFont.load("OpenSans-regular.ttf", 50);
    wallFontSmall.load("OpenSans-regular.ttf", 40);

    //channels gui
    channelsButtons[0].x = 100;
    channelsButtons[0].y = 300;
    channelsButtons[0].width = 200;
    channelsButtons[0].height = 200;

    channelsButtons[1].x = 400;
    channelsButtons[1].y = 300;
    channelsButtons[1].width = 200;
    channelsButtons[1].height = 200;

    channelsButtons[2].x = 700;
    channelsButtons[2].y = 300;
    channelsButtons[2].width = 200;
    channelsButtons[2].height = 200;

    playChanButtons.x = 100;
    playChanButtons.y = 510;
    playChanButtons.width = 400;
    playChanButtons.height = 80;

    stopChanButtons.x = 100;
    stopChanButtons.y = 600;
    stopChanButtons.width = 400;
    stopChanButtons.height = 80;

    changeMode.x = 1000;
    changeMode.y = 80;
    changeMode.width = 200;
    changeMode.height = 80;
    //XML Setting
    loadChannelFromXml();


    seq.setup(SEQIP, SEQPORT);

}

/*
void ofApp::switchMedia(int & wich){
    loading = true;
    vid.stop();
    vid.closeMovie();
    vid.load(media.getPath(wich));
    vid.setLoopState(OF_LOOP_NORMAL);

    //fetch size for texture
    vHeight = vid.getHeight();
    vWidth = vid.getWidth();

    for(int i = 0; i<maxSel; i++){
        m_selections[i].x = ofMap(selections[i].x, 0, sliceW, 0, 1.0);
        m_selections[i].y = ofMap(selections[i].y, 0, sliceH, 0, 1.0);
        m_selections[i].width  = ofMap(selections[i].width, 0, sliceW, 0, 1.0);
        m_selections[i].height = ofMap(selections[i].height, 0, sliceH, 0, 1.0);
    }
    vid.play();
    remapSel(vWidth, vHeight);
    loading = false;
 }
*/
void ofApp::switchMedia(int wich){

    //vHeight = imgz[wich].getHeight();
    //vWidth = imgz[wich].getWidth();

    vHeight = images[wich].getHeight();
    vWidth = images[wich].getWidth();

    for(int i = 0; i<maxSel; i++){
        m_selections[i].x = (int)ofMap(selections[i].x, 0, sliceW, 0, vWidth);
        m_selections[i].y = (int)ofMap(selections[i].y, 0, sliceH, 0, vHeight);
        m_selections[i].width  = (int)ofMap(selections[i].width, 0, sliceW, 0, vWidth);
        m_selections[i].height = (int)ofMap(selections[i].height, 0, sliceH, 0, vHeight);
    }
    remapSel(vWidth, vHeight);
    loading = false;
}

void ofApp::loadMedia(string path, int numFiles){

    ofxImageSequence * img = new ofxImageSequence();
    img->loadSequence(loadPath+path, "jpg",  0, numFiles);
    img->preloadAllFrames();
    img->setFrameRate(13);
    images.push_back(*img);

    numLoaded++;

}

void ofApp::remapSel(int vidW, int vidH){

    for(int i = 0; i<maxSel; i++){

        cout<<"mapping for selection: " + ofToString(i) <<endl;
        m_selections[i].x = ofMap(selections[i].x, 0, sliceW, 0, 1.0);
        m_selections[i].y = ofMap(selections[i].y, 0, sliceH, 0, 1.0);
        m_selections[i].width  = ofMap(selections[i].width, 0, sliceW, 0, 1.0);
        m_selections[i].height = ofMap(selections[i].height, 0, sliceH, 0, 1.0);
        /*
        cout<<"X: " + ofToString(m_selections[i].x)<<endl;
        cout<<"Y: " + ofToString(m_selections[i].y)<<endl;
        cout<<"W: " + ofToString(m_selections[i].width)<<endl;
        cout<<"H: " + ofToString(m_selections[i].height)<<endl;
        */
        cout<<"mapping textcoords"<<endl;
        videoProjections[i].mapTexCoords(m_selections[i].x, m_selections[i].y, m_selections[i].x + m_selections[i].width , m_selections[i].y + m_selections[i].height);
    }


}
//--------------------------------------------------------------wichSel = 0;
void ofApp::update(){

    while(receiver.hasWaitingMessages()){

            ofxOscMessage m;
            receiver.getNextMessage(&m);
            ofLog(OF_LOG_NOTICE, "received OSC");
            if(m.getAddress()=="/LOAD"){
                ofLog(OF_LOG_NOTICE, m.getArgAsString(0));

                loadMedia(m.getArgAsString(0), m.getArgAsInt32(1));

            }else if(m.getAddress() == "/CLEAR"){

                numLoaded = 0;
                images.clear();
            }
        }

    if(animate){
            for(int i = 0; i<4;i++){
                selections[i].x += velo[i].x ;
                selections[i].y += velo[i].y ;

                m_selections[i].x = ofMap(selections[i].x, 0, sliceW, 0, 1.0);
                m_selections[i].y = ofMap(selections[i].y, 0, sliceH, 0, 1.0);

                if (selections[i].x<0 || selections[i].x + selections[i].width > sliceW) {
                        velo[i].x = -velo[i].x;
                }

                if (selections[i].y<0 || selections[i].y + selections[i].height > sliceH) {
                        velo[i].y = -velo[i].y;
                }

                videoProjections[i].mapTexCoords(m_selections[i].x, m_selections[i].y, m_selections[i].x + m_selections[i].width , m_selections[i].y + m_selections[i].height);
            }
                ofxOscMessage locMess1;
                locMess1.setAddress("/LOC");

                locMess1.addFloatArg(m_selections[0].x);
                locMess1.addFloatArg(m_selections[0].y);
                locMess1.addFloatArg(m_selections[0].width);
                locMess1.addFloatArg(m_selections[0].height);

                ctlz[0].sendMessage(locMess1);

                ofxOscMessage locMess2;
                locMess2.setAddress("/LOC");

                locMess2.addFloatArg(m_selections[1].x);
                locMess2.addFloatArg(m_selections[1].y);
                locMess2.addFloatArg(m_selections[1].width);
                locMess2.addFloatArg(m_selections[1].height);

                ctlz[1].sendMessage(locMess2);

                ofxOscMessage locMess3;
                locMess3.setAddress("/LOC");

                locMess3.addFloatArg(m_selections[2].x);
                locMess3.addFloatArg(m_selections[2].y);
                locMess3.addFloatArg(m_selections[2].width);
                locMess3.addFloatArg(m_selections[2].height);

                ctlz[2].sendMessage(locMess3);

    }

}

//--------------------------------------------------------------
void ofApp::draw(){
       if(mode2show == 0){
            bgImage.draw(0, 0);
            ofPushStyle();

                ofNoFill();
                ofSetColor(0, 0, 0);
                wallFont.drawString("WALL", ofGetWidth()/2-100, 80);
                wallFont.drawString("CHANNELS", ofGetWidth()/2-210, 200);
                ofRect(changeMode.x, changeMode.y, changeMode.width, changeMode.height);
                //ofRect(channelsButtons[i].x, channelsButtons[i].y, channelsButtons[i].width, channelsButtons[i].height);
                ofRect(playChanButtons.x, playChanButtons.y, playChanButtons.width, playChanButtons.height);
                ofRect(stopChanButtons.x, stopChanButtons.y, stopChanButtons.width, stopChanButtons.height);
                wallFontSmall.drawString("play", playChanButtons.x + 150, playChanButtons.y + 50);
                wallFontSmall.drawString("stop", stopChanButtons.x + 150, stopChanButtons.y + 50);
                for(int i = 0; i<3;i++){
                    wallFontSmall.drawString(channelsNames[i], channelsButtons[i].x, channelsButtons[i].y - 20);
                }
            ofPopStyle();
            ofPushStyle();
                for(int i = 0; i<3; i++){

                    if(previewLoaded == true){
                         previewImgs[i].draw(channelsButtons[i].x, channelsButtons[i].y, channelsButtons[i].width, channelsButtons[i].height);
                         }
                }
            ofPopStyle();
       }
        else if(mode2show == 1){
        bgImage.draw(0, 0);
        if(numLoaded>0){
            //vid.draw(0, 0, sliceW, sliceH);
            //seqz[wichVid].getFrameForTime(ofGetElapsedTimef())->draw(0,0, sliceW, sliceH);
            //imgz[wichVid].draw(0, 0, sliceW, sliceH);
            images[wichVid].getFrameForTime(ofGetElapsedTimef())->draw(0, 0, sliceW, sliceH);

        }

        if(!loading && numLoaded>0){
            for(int i = 0; i<4; i++){
                //old
                /*
                imgz[wichVid].getTextureReference().bind();
                     videoProjections[i].draw();
                imgz[wichVid].getTextureReference().unbind();
                */

                images[wichVid].getTextureReference().bind();
                    videoProjections[i].draw();
                images[wichVid].getTextureReference().unbind();


                /*
                imgz[vidMap[i]].getTextureReference().bind();
                    videoProjections[i].draw();
                imgz[vidMap[i]].getTextureReference().unbind();
                */

                ofNoFill();
                ofSetLineWidth(2);
                if(i == wichSel){
                    ofSetColor(255, 0, 0);
                }else{
                    ofSetColor(255, 255, 255);
                }

                ofRect(selections[i].x, selections[i].y, selections[i].width, selections[i].height);
                ofSetColor(255, 255, 255);
                ofSetLineWidth(1);
            }
        }
        ofNoFill();
            ofSetColor(0,0, 0);
            ofRect(changeZone.x, changeZone.y, changeZone.width, changeZone.height);
            ofRect(animZone.x, animZone.y, animZone.width, animZone.height);
            ofRect(mapZone.x, mapZone.y, mapZone.width, mapZone.height);
            ofRect(changeMode.x, changeMode.y, changeMode.width, changeMode.height);

            //testing
            ofRect(sliceZone.x, sliceZone.y, sliceZone.width, sliceZone.height);
            //videoProjections[3].drawWireframe();
            //ofRect(dev4.x, dev4.y, dev4.width, dev4.height);


        ofNoFill();
        ofSetColor(0, 0, 0);
            wallFontSmall.drawString(labels[0], changeZone.x+10, changeZone.y+50);
            wallFontSmall.drawString(labels[2], animZone.x+10, animZone.y+50);
            wallFontSmall.drawString(labels[1], mapZone.x+10, mapZone.y+50);
            //ofRect(dev3.x, dev3.y, dev3.width, dev3.height);
        ofSetColor(255, 255, 255);

       }
}

void ofApp::touchDown(int x, int y, int id){

    if(mode2show == 1){
        if(sliceZone.inside(x, y)){
            selecting = true;

            selections[wichSel].x = x  ;
            selections[wichSel].y = y ;

            m_selections[wichSel].x = ofMap(selections[wichSel].x, 0, sliceW, 0, 1.0);
            m_selections[wichSel].y = ofMap(selections[wichSel].y, 0, sliceH, 0, 1.0);
    }
   }
}

void ofApp::touchMoved(int x, int y, int id){
    if(mode2show == 1){
        if(sliceZone.inside(x, y)){
            selections[wichSel].width = x - selections[wichSel].x;
            selections[wichSel].height = y - selections[wichSel].y;

            m_selections[wichSel].width  = ofMap(selections[wichSel].width, 0, sliceW, 0, 1.0);
            m_selections[wichSel].height = ofMap(selections[wichSel].height, 0, sliceH, 0, 1.0);
        }
    //cout<<m_selections[wichSel].width<<endl;
    }
}

void ofApp::touchUp(int x, int y, int id){

    if(changeMode.inside(x, y)){
         ofLog(OF_LOG_NOTICE, "change mode2show");
         if(mode2show == 0){
            mode2show = 1;
         }else if(mode2show ==1){
            mode2show = 0;
            images.clear();
            numLoaded = 0;
         }
    }

    if(mode2show == 1){


        if(mapZone.inside(x, y)){

            mapMode = true;
        }
        else if(sliceZone.inside(x, y)){

            if(selections[wichSel].width>10 && selections[wichSel].height>10){
                videoProjections[wichSel].mapTexCoords(m_selections[wichSel].x, m_selections[wichSel].y, m_selections[wichSel].x + m_selections[wichSel].width , m_selections[wichSel].y + m_selections[wichSel].height);
            //remapSel(vWidth, vHeight);
                selecting = false;
            //wichSel = (wichSel +1)%3;

            //sending LOCS to CLIENTS
                ofLog(OF_LOG_NOTICE, "send osc");
                if(wichSel == 0){
                    ofxOscMessage locMess1;
                    locMess1.setAddress("/LOC");

                    locMess1.addFloatArg(m_selections[wichSel].x);
                    locMess1.addFloatArg(m_selections[wichSel].y);
                    locMess1.addFloatArg(m_selections[wichSel].width);
                    locMess1.addFloatArg(m_selections[wichSel].height);

                    ctlz[wichSel].sendMessage(locMess1);
                }else if(wichSel == 1){

                    ofxOscMessage locMess2;
                    locMess2.setAddress("/LOC");

                    locMess2.addFloatArg(m_selections[wichSel].x);
                    locMess2.addFloatArg(m_selections[wichSel].y);
                    locMess2.addFloatArg(m_selections[wichSel].width);
                    locMess2.addFloatArg(m_selections[wichSel].height);

                    ctlz[wichSel].sendMessage(locMess2);

                }else if(wichSel == 2){

                    ofxOscMessage locMess3;
                    locMess3.setAddress("/LOC");

                    locMess3.addFloatArg(m_selections[wichSel].x);
                    locMess3.addFloatArg(m_selections[wichSel].y);
                    locMess3.addFloatArg(m_selections[wichSel].width);
                    locMess3.addFloatArg(m_selections[wichSel].height);

                    ctlz[wichSel].sendMessage(locMess3);
                }
                else if(wichSel == 3){

                    ofxOscMessage locMess4;
                    locMess4.setAddress("/LOC");

                    locMess4.addFloatArg(m_selections[wichSel].x);
                    locMess4.addFloatArg(m_selections[wichSel].y);
                    locMess4.addFloatArg(m_selections[wichSel].width);
                    locMess4.addFloatArg(m_selections[wichSel].height);

                    ctlz[wichSel].sendMessage(locMess4);
                }
            }
        }else if(changeZone.inside(x, y)){


            wichVid = (wichVid +1)%numLoaded;
            switchMedia(wichVid);


        }else if(dev1.inside(x, y)){
            wichSel = 0;
            if(mapMode == true){
            ofLog(OF_LOG_NOTICE, "sending: "+ ofToString(wichSel)+" -> " + ofToString(wichVid));
            ofxOscMessage numVid;
            numVid.setAddress("/NUMVID");
            numVid.addIntArg(wichVid);
            ctlz[wichSel].sendMessage(numVid);
            vidMap[wichSel] = wichVid;
            mapMode = false;

            /*
            ofLog(OF_LOG_NOTICE, "sending map: "+ofToString(wichVid));
            vidMap[wichSel] = wichVid;
            ofLog(OF_LOG_NOTICE, "map updated");
            ofLog(OF_LOG_NOTICE, "sending map to OSC");
            getNumFilesInDir(loadPath+fileNames[wichVid]);
            ofLog(OF_LOG_NOTICE, "done sending map");
            mapMode = false;
            */
        }
        }else if(dev2.inside(x, y)){
            wichSel = 1;
            if(mapMode == true){
            ofLog(OF_LOG_NOTICE, "sending: "+ ofToString(wichSel)+" -> " + ofToString(wichVid));
            ofxOscMessage numVid;
             numVid.setAddress("/NUMVID");
            numVid.addIntArg(wichVid);
            ctlz[wichSel].sendMessage(numVid);
            vidMap[wichSel] = wichVid;
            mapMode = false;

                /*
                vidMap[wichSel] = wichVid;
                mapMode = false;
                getNumFilesInDir(loadPath+fileNames[wichVid]);
                */
            }
        }else if(dev3.inside(x, y)){
            wichSel = 2;
            if(mapMode == true){
            ofLog(OF_LOG_NOTICE, "sending: "+ ofToString(wichSel)+" -> " + ofToString(wichVid));
            ofxOscMessage numVid;
            numVid.setAddress("/NUMVID");
            numVid.addIntArg(wichVid);
            ctlz[wichSel].sendMessage(numVid);
            vidMap[wichSel] = wichVid;
            mapMode = false;

               /*
                vidMap[wichSel] = wichVid;
                mapMode = false;
                getNumFilesInDir(loadPath+fileNames[wichVid]);
                */
            }

        }else if(dev4.inside(x, y)){
                    wichSel = 3;
                    if(mapMode == true){
                    ofLog(OF_LOG_NOTICE, "sending: "+ ofToString(wichSel)+" -> " + ofToString(wichVid));
                    ofxOscMessage numVid;
                    numVid.setAddress("/NUMVID");
                    numVid.addIntArg(wichVid);
                    ctlz[wichSel].sendMessage(numVid);
                    vidMap[wichSel] = wichVid;
                    mapMode = false;

                        /*
                        vidMap[wichSel] = wichVid;
                        mapMode = false;
                        getNumFilesInDir(loadPath+fileNames[wichVid]);
                        */
                    }
        }else if(animZone.inside(x, y)){
            animate = !animate;

        }
    }
    if(mode2show == 0){

        for(int i = 0; i<3;i++){

            if(channelsButtons[i].inside(x, y)){
              ofLog(OF_LOG_NOTICE, "sending channel: " + ofToString(i));
              switchChannels(channelsNames[i]);
              sendLoadSequence(i);
            }
        }

        if(playChanButtons.inside(x, y)){
            sendStartSequence();
        }
        if(stopChanButtons.inside(x, y)){
            sendStopSequence();
        }

    }
}

void ofApp::sendWich2Load(int dest, string file, int numFiles){

    cout<<"sending load Message"<<endl;
    ofxOscMessage loadMess;
    loadMess.setAddress("/LOAD");
    loadMess.addStringArg(file);
    loadMess.addIntArg(numFiles);

    ctlz[dest].sendMessage(loadMess);
}

void ofApp::getNumFilesInDir(string dir){
    ofLog(OF_LOG_NOTICE, "scandir");
    ofDirectory dir2scan(dir);
    dir2scan.allowExt("jpg");
    dir2scan.listDir();
    ofLog(OF_LOG_NOTICE, "loading media");
    ofxImageSequence *img = new ofxImageSequence();;
    img->loadSequence(dir+"/", "jpg", 0, dir2scan.size()-1);
    //img->preloadAllFrames();
    img->setFrameRate(13);
    images.push_back(*img);
    //mediaType.push_back(1);
    //wichMedia++;
    //switchMedia(wichMedia);
    numLoaded++;
    ofLog(OF_LOG_NOTICE, "done loading media");
    ofLog(OF_LOG_NOTICE, ofToString(numLoaded));
    //string split = ofSplitString(dir, "/home/ekko/wall_box/Dropbox/wall_box/")[1];
    //sendWich2Load(wichSel, destLoadPath+fileNames[wichVid], dir2scan.size()-1);

}

void ofApp::loadChannelFromXml(){

    ofLog(OF_LOG_NOTICE, "scan for XMLs");
    ofDirectory dir2scan(loadPath);
    dir2scan.allowExt("xml");
    dir2scan.listDir();
    ofLog(OF_LOG_NOTICE, ofToString(dir2scan.size()));

    for(int i = 0; i<dir2scan.size(); i++){
        channelsNames[i] = dir2scan.getName(i);


        ofxXmlSettings chanSettings;
        chanSettings.loadFile(dir2scan.getPath(i));

            chanSettings.pushTag("media");
                chanSettings.pushTag("file", 0);

                    string split = ofSplitString(chanSettings.getValue("name", "ffff"), seqPath)[1];

                    ofLog(OF_LOG_NOTICE, loadPath+split+"/"+"0.jpg");

                    previewImgs[i].load(loadPath+split+"/"+"0.jpg");

            chanSettings.popTag();
        chanSettings.popTag();
        previewLoaded = true;
    }
}

void ofApp::switchChannels(string channel_Name){
    sendClear();

    ofxXmlSettings chanSettings;
    ofLog(OF_LOG_NOTICE, "get chanel:"+loadPath+channel_Name);
    chanSettings.load(loadPath+channel_Name);

        chanSettings.pushTag("media");
            for(int i = 0; i<chanSettings.getNumTags("file"); i++){

                chanSettings.pushTag("file", i);
                    string split = ofSplitString(chanSettings.getValue("name", "ffff"), seqPath)[1];
                    ofLog(OF_LOG_NOTICE, destLoadPath+split);
                    ofLog(OF_LOG_NOTICE, loadPath+split);

                    getNumFilesInDir(loadPath+split);
                    ofxOscMessage loadMess;
                    loadMess.setAddress("/LOAD");
                    loadMess.addStringArg(destLoadPath+split);

                    for(int i = 0;i<4;i++){

                        ctlz[i].sendMessage(loadMess);
                    }
                chanSettings.popTag();
            }
        chanSettings.popTag();
}

void ofApp::sendClear(){

    ofxOscMessage clearMess;
    clearMess.setAddress("/CLEAR");
    for(int i = 0; i<4;i++){
        ctlz[i].sendMessage(clearMess);
    }
}

void ofApp::sendStartSequence(){

    ofxOscMessage startMess;
    startMess.setAddress("/PLAY");

    seq.sendMessage(startMess);

}

void ofApp::sendStopSequence(){

    ofxOscMessage stopMess;
    stopMess.setAddress("/STOP");

    seq.sendMessage(stopMess);
}

void ofApp::sendLoadSequence(unsigned int sequence){

    ofxOscMessage sequenceMess;
    sequenceMess.setAddress("/SEQ");
    sequenceMess.addIntArg(sequence);

    seq.sendMessage(sequenceMess);


}