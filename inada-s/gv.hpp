#pragma once
/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 colun ( Yasunobu Imamura )
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef NDEBUG
#include <assert.h>
#include <math.h>
#include <stdarg.h>
#include <functional>

#ifdef _WIN32
#include <io.h>
#define M_PI 3.14159265358979323846
#define ftruncate _chsize
#define fileno _fileno
#else
#include <netdb.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

const auto gv_js = R"###(
<script>
(function(t,x,y){function a(D,z){function A(){}A.prototype=D;var C=new A();for(var B in z){C[B]=z[B]}if(z.toString!==Object.prototype.toString){C.toString=z.toString}return C}var k=function(){};k.__name__=true;k.strDate=function(B){var E=B.length;switch(E){case 8:var z=B.split(":");var D=new Date();D.setTime(0);D.setUTCHours(z[0]);D.setUTCMinutes(z[1]);D.setUTCSeconds(z[2]);return D;case 10:var G=B.split("-");return new Date(G[0],G[1]-1,G[2],0,0,0);case 19:var C=B.split(" ");var F=C[0].split("-");var A=C[1].split(":");return new Date(F[0],F[1]-1,F[2],A[0],A[1],A[2]);default:throw new o("Invalid date format : "+B)}};k.iter=function(z){return{cur:0,arr:z,hasNext:function(){return this.cur<this.arr.length},next:function(){return this.arr[this.cur++]}}};var c=function(){this.length=0};c.__name__=true;c.prototype={add:function(A){var z=[A];if(this.h==null){this.h=z}else{this.q[1]=z}this.q=z;this.length++},__class__:c};Math.__name__=true;var g=function(){};g.__name__=true;g.string=function(z){return l.__string_rec(z,"")};g["int"]=function(z){return z|0};var h=function(){};h.__name__=true;h.newTime=x.n=function(z){e.newTime(z)};h.circle=x.c=function(z,C,B){if(B==null){B=0.5}var A=new s(z,C,B);e.addItem(A);return A};h.text=x.t=function(C,z,D,B){if(B==null){B=0.5}var A=new p(C,z,D,B);e.addItem(A);return A};h.polygon=x.p=function(){var z=arguments;var A=new d();var C=0;var D;D=l.__cast(z.length/2,i);while(C<D){var B=C++;A.add(z[B*2],z[B*2+1])}e.addItem(A);return A};h.line=x.l=function(G,E,H,F,z){if(z==null){z=0.5}var D=new d();var B=H-G;var A=F-E;var C=z/Math.sqrt(B*B+A*A);var J=B*C;var I=A*C;D.add(H+I*(0.05/(1+Math.sqrt(2))),F+J*(0.05/(1+Math.sqrt(2))));D.add(H-J*(0.05*Math.sqrt(2)/(1+Math.sqrt(2)))-I*0.05,F-I*(0.05*Math.sqrt(2)/(1+Math.sqrt(2)))+J*0.05);D.add(G+J*(0.05*Math.sqrt(2)/(1+Math.sqrt(2)))-I*0.05,E+I*(0.05*Math.sqrt(2)/(1+Math.sqrt(2)))+J*0.05);D.add(G-I*(0.05/(1+Math.sqrt(2))),E+J*(0.05/(1+Math.sqrt(2))));D.add(G+I*(0.05/(1+Math.sqrt(2))),E-J*(0.05/(1+Math.sqrt(2))));D.add(G+J*(0.05*Math.sqrt(2)/(1+Math.sqrt(2)))+I*0.05,E+I*(0.05*Math.sqrt(2)/(1+Math.sqrt(2)))-J*0.05);D.add(H-J*(0.05*Math.sqrt(2)/(1+Math.sqrt(2)))+I*0.05,F-I*(0.05*Math.sqrt(2)/(1+Math.sqrt(2)))-J*0.05);D.add(H+I*(0.05/(1+Math.sqrt(2))),F-J*(0.05/(1+Math.sqrt(2))));e.addItem(D);return D};h.out=x.o=function(z){e.addOut(z)};h.autoMode=x.a=function(){e.autoMode()};var e=function(){};e.__name__=true;e.newTime=function(z){if(z==null){e.nowTime=g["int"](0.1+Math.max(0,e.maxTime+1))}else{e.maxTime=g["int"](0.1+Math.max(e.maxTime,z));e.nowTime=z}};e.addItem=function(B){if(e.emptyFlag){e.emptyFlag=false;e.minX=B.getMinX();e.minY=B.getMinY();e.maxX=B.getMaxX();e.maxY=B.getMaxY();e.maxTime=e.nowTime}else{e.minX=Math.min(e.minX,B.getMinX());e.minY=Math.min(e.minY,B.getMinY());e.maxX=Math.max(e.maxX,B.getMaxX());e.maxY=Math.max(e.maxY,B.getMaxY());e.maxTime=g["int"](0.1+Math.max(e.maxTime,e.nowTime))}if(e.snapMap.h.hasOwnProperty(e.nowTime)){var z=e.snapMap.h[e.nowTime];z.addItem(B)}else{var A=new b(e.nowTime);e.snapMap.h[e.nowTime]=A;A.addItem(B)}};e.addOut=function(z){if(e.outMap.h.hasOwnProperty(e.nowTime)){var A=e.outMap.h[e.nowTime];e.outMap.h[e.nowTime]=""+A+z+"\n"}else{e.outMap.h[e.nowTime]=""+z+"\n"}};e.getMinX=function(){return e.minX};e.getMinY=function(){return e.minY};e.getMaxX=function(){return e.maxX};e.getMaxY=function(){return e.maxY};e.getTimeList=function(){var A=[];var B=e.snapMap.keys();while(B.hasNext()){var z=B.next();A.push(z)}return A};e.getSnap=function(z){return e.snapMap.h[z]};e.getOut=function(z){if(e.outMap.h.hasOwnProperty(z)){return e.outMap.h[z]}else{return""}};e.getAutoModeCount=function(){return e.autoModeCount};e.sendInput=function(C,z,D){if(e.inputInt_!=null){var B=e.inputInt_;e.inputInt_=null;B(C,Math.round(z),Math.round(D))}else{if(e.inputFloat_!=null){var A=e.inputFloat_;e.inputFloat_=null;A(C,z,D)}}};e.gvGetColorFromIndex=function(z){return e.colors[z]};e.inputInt=function(z){e.inputInt_=z;e.inputFloat_=null};e.inputFloat=function(z){e.inputFloat_=z;e.inputInt_=null};e.setDragModeInt=function(B,A,z){e.dragStartInt_=B;e.dragStartFloat_=null;e.dragMoveInt_=A;e.dragMoveFloat_=null;e.dragEnd_=z};e.setDragModeFloat=function(B,A,z){e.dragStartInt_=B;e.dragStartFloat_=null;e.dragMoveInt_=A;e.dragMoveFloat_=null;e.dragEnd_=z};e.isDragMode=function(){return e.dragStartInt_!=null||e.dragStartFloat_!=null};e.isNowDrag=function(){return e.nowDragFlag};e.sendDragStart=function(C,z,D){e.sendDragEnd();if(e.dragStartInt_!=null){var B=e.dragStartInt_;e.nowDragFlag=true;B(C,Math.round(z),Math.round(D))}else{if(e.dragStartFloat_!=null){var A=e.dragStartFloat_;e.nowDragFlag=true;A(C,z,D)}}};e.sendDragMove=function(C,z,D){if(e.nowDragFlag){if(e.dragMoveInt_!=null){var B=e.dragMoveInt_;B(Math.round(z),Math.round(D))}else{if(e.dragMoveFloat_!=null){var A=e.dragMoveFloat_;A(z,D)}}}};e.sendDragEnd=function(){if(e.nowDragFlag){if(e.dragEnd_!=null){var z=e.dragEnd_;z()}e.nowDragFlag=false}};e.autoMode=function(){++e.autoModeCount};e.rgb=function(C,B,z,A){if(A==null){A=1}return"rgba("+C*100+"%, "+B*100+"%, "+z*100+"%, "+A};var q=function(){};q.__name__=true;q.main=function(){window.onload=function(F){q.canvas=window.document.createElement("canvas");window.document.body.appendChild(q.canvas);q.canvas.style.position="absolute";q.canvas.style.left="0px";q.canvas.style.top="0px";q.canvas.style.width="100%";q.canvas.style.height="100%";q.canvas.width=window.innerWidth;q.canvas.height=window.innerHeight;q.ctx=q.canvas.getContext("2d",null);q.div=window.document.createElement("pre");window.document.body.appendChild(q.div);q.div.style.position="absolute";q.div.style.left="0px";q.div.style.bottom="0px";window.onresize=function(N){q.canvas.width=window.innerWidth;q.canvas.height=window.innerHeight;q.updateUI()};window.onkeydown=function(O){var N=O.keyCode;switch(N){case 33:q.autoMode=false;if(1<=q.now){q.now=g["int"](Math.max(0,q.now-g["int"](Math.max(10,Math.sqrt(q.timeList.length)))));q.updateTime()}break;case 34:q.autoMode=false;if(q.timeList!=null&&q.now<q.timeList.length-1){q.now=g["int"](Math.min(q.now+Math.max(10,g["int"](Math.sqrt(q.timeList.length))),q.timeList.length-1));q.updateTime()}break;case 35:q.autoMode=false;if(q.timeList!=null&&q.now<q.timeList.length-1){q.now=q.timeList.length-1;q.updateTime()}break;case 36:q.autoMode=false;if(1<=q.now){q.now=0;q.updateTime()}break;case 37:q.autoMode=false;if(1<=q.now){--q.now;q.updateTime()}break;case 38:q.updateSelf(null,false,4,false,false);break;case 39:q.autoMode=false;if(q.timeList!=null&&q.now<q.timeList.length-1){++q.now;q.updateTime()}break;case 40:q.updateSelf(null,false,-4,false,false);break;case 97:q.onNumpadKey(-0.7,0.7);break;case 98:q.onNumpadKey(0,1);break;case 99:q.onNumpadKey(0.7,0.7);break;case 100:q.onNumpadKey(-1,0);break;case 102:q.onNumpadKey(1,0);break;case 103:q.onNumpadKey(-0.7,-0.7);break;case 104:q.onNumpadKey(0,-1);break;case 105:q.onNumpadKey(0.7,-0.7);break}};var M=false;window.onmousedown=function(N){M=true;q.myMouseX=N.clientX;q.myMouseY=N.clientY;q.updateSelf(null,false,0,false,N.shiftKey);return false};window.onmouseup=function(N){M=false;q.myMouseX=N.clientX;q.myMouseY=N.clientY;q.updateSelf(null,false,0,false,false);if(e.isDragMode()){if(e.isNowDrag()){e.sendDragEnd();q.updateTimeList()}}return false};window.onmousemove=function(N){q.myMouseX=N.clientX;q.myMouseY=N.clientY;q.updateSelf(null,M,0,false,false);return false};window.onwheel=function(N){q.myMouseX=N.clientX;q.myMouseY=N.clientY;var P;if(0<N.detail){P=-1}else{if(N.detail<0){P=1}else{P=0}}if(P==0){var O=N.wheelDelta;if(0<O){P=1}else{if(O<0){P=-1}else{P=0}}}q.updateSelf(null,false,P,false,false);return false};var K=null;var J=null;var G=null;var H=0;var B=0;var D=12.425134878021495/Math.log(2);var E=new j();var I=function(Q){if(B!=Q.touches.length){K=null}B=Q.touches.length;if(1<=Q.touches.length){var ad=0;var P=Q.touches.length;while(ad<P){var ak=ad++;var aa=Q.touches.item(ak);if(!E.h.hasOwnProperty(aa.identifier)){K=null}}var O=0;var N=0;var aj=0;var ac=Q.touches.length;while(aj<ac){var ag=aj++;var V=Q.touches.item(ag);O+=V.pageX;N+=V.pageY}var U=O/Q.touches.length;var T=N/Q.touches.length;var Z=0;var ai=0;var ab=Q.touches.length;while(ai<ab){var af=ai++;var S=Q.touches.item(af);var X=S.pageX-U;var W=S.pageY-T;Z+=Math.sqrt(X*X+W*W+0.00001)}var an=Z/Q.touches.length;if(K!=null){if(3<=Q.touches.length){q.autoMode=false;var al=10*(U-K)/q.canvas.width;var ao;ao=H-(0<=al?Math.floor(al):Math.ceil(al));if(ao!=q.now&&q.timeList!=null&&0<=ao&&ao<q.timeList.length){q.now=ao;q.updateTime()}}else{if(2==Q.touches.length){var am=Math.log(an/G)*D;q.myMouseX=U;q.myMouseY=T;q.updateSelf(null,false,am,false,false);K=U;J=T;G=an}else{if(1==Q.touches.length){q.myMouseX=U;q.myMouseY=T;q.updateSelf(null,true,0,false,false);K=U;J=T;G=an}}}}else{q.myMouseX=U;q.myMouseY=T;q.updateSelf(null,false,0,false,false);K=U;J=T;G=an;H=q.now}}E=new j();var ah=0;var Y=Q.touches.length;while(ah<Y){var ae=ah++;var R=Q.touches.item(ae);E.h[R.identifier]=true}Q.preventDefault();return false};window.ontouchmove=I;var C=null;var A=null;var z=null;var L=k.strDate("2000-01-01 00:00:01").getTime()-k.strDate("2000-01-01 00:00:00").getTime();window.ontouchstart=function(O){K=null;if(O.touches.length==1){var Q=O.touches.item(0).pageX;var R=O.touches.item(0).pageY;var P=new Date().getTime();if(z!=null&&P-z<=L*0.5){var T=Q-C;var N=R-A;var S=Math.sqrt(T*T+N*N);if(S<=Math.min(q.canvas.width,q.canvas.height)*0.05){q.myMouseX=Q;q.myMouseY=R;q.updateSelf(null,false,0,false,true);O.preventDefault();return false}}C=Q;A=R;z=P}I(O);return false};window.ontouchcancel=function(N){K=null;N.preventDefault();return false};window.ontouchend=function(N){K=null;N.preventDefault();if(N.targetTouches.length==N.touches.length){if(e.isDragMode()){if(e.isNowDrag()){e.sendDragEnd();q.updateTimeList()}}}return false};q.updateTimeList()}};q.onNumpadKey=function(A,z){var C=Math.min(Math.max(-q.mx,q.cx+A*q.scale*0.25),q.mx);var B=Math.min(Math.max(-q.my,q.cy+z*q.scale*0.25),q.my);if(q.cx!=C||q.cy!=B){q.cx=C;q.cy=B;q.updateUI()}};q.updateUI=function(){if(q.paintTimer!=null){window.clearTimeout(q.paintTimer)}q.paintTimer=window.setTimeout(q.paintSelf,10)};q.paintSelf=function(){q.paintTimer=null;q.updateSelf(q.ctx,false,0,false,false)};q.updateSelf=function(Q,U,z,D,B){var P=Math.max(1,q.canvas.width);var N=Math.max(1,q.canvas.height);var L=e.getMaxX()-e.getMinX();var J=e.getMaxY()-e.getMinY();var E=Math.max(L,J);var V;var O;var M;if(L*N<J*P){q.my=(1-q.scale)*0.5;V=N/(J*q.scale);if(V*L<=P){q.mx=0}else{q.mx=(L-P/V)/E*0.5}}else{q.mx=(1-q.scale)*0.5;V=P/(L*q.scale);if(V*J<=N){q.my=0}else{q.my=(J-N/V)/E*0.5}}q.updateCenter();var I=q.cursorX;var G=q.cursorY;if(D){q.cx=(q.cursorX-(q.myMouseX-P*0.5)/V-L*0.5-e.getMinX())/E;q.cy=(q.cursorY-(q.myMouseY-N*0.5)/V-J*0.5-e.getMinY())/E;q.updateCenter();return}q.cursorX=(q.myMouseX-P*0.5)/V+L*0.5+e.getMinX()+E*q.cx;q.cursorY=(q.myMouseY-N*0.5)/V+J*0.5+e.getMinY()+E*q.cy;if(q.nowSnap==null){return}var F=q.nowSnap.getTime();if(U){if(e.isDragMode()){if(!e.isNowDrag()){e.sendDragStart(F,I,G)}e.sendDragMove(F,q.cursorX,q.cursorY);q.updateTimeList()}else{var K=q.cursorX-I;var H=q.cursorY-G;var C=q.cx;var A=q.cy;q.cx-=K/E;q.cy-=H/E;q.updateCenter();if(C!=q.cx||A!=q.cy){if(z!=0){q.cursorX=(q.myMouseX-P*0.5)/V+L*0.5+e.getMinX()+E*q.cx;q.cursorY=(q.myMouseY-N*0.5)/V+J*0.5+e.getMinY()+E*q.cy;var S=Math.min(Math.max(0.01,q.scale*Math.pow(0.5,z*0.080482023721841)),1);if(q.scale!=S){q.scale=S;q.updateSelf(null,false,0,true,false)}}q.updateUI();return}}}if(z!=0){var T=Math.min(Math.max(0.01,q.scale*Math.pow(0.5,z*0.080482023721841)),1);if(q.scale!=T){q.scale=T;q.updateSelf(null,false,0,true,false);q.updateUI();return}}if(B){e.sendInput(F,q.cursorX,q.cursorY);q.updateTimeList()}var R=e.getOut(F);if(0<=q.myMouseX&&0<=q.myMouseY&&e.getMinX()<=q.cursorX&&q.cursorX<=e.getMaxX()&&e.getMinY()<=q.cursorY&&q.cursorY<=e.getMaxY()){q.div.textContent=""+R+"time "+F+" ( "+(q.now+1)+" / "+q.timeList.length+" ) ("+(q.cursorX+0.5|0)+", "+(q.cursorY+0.5|0)+") ("+q.cursorX+", "+q.cursorY+")"}else{q.div.textContent=""+R+"time "+F+" ( "+(q.now+1)+" / "+q.timeList.length+" )"}O=(P/V-L)*0.5-e.getMinX()-E*q.cx;M=(N/V-J)*0.5-e.getMinY()-E*q.cy;if(Q!=null){Q.clearRect(0,0,P,N);Q.save();Q.scale(V,V);Q.translate(O,M);q.nowSnap.paint(Q);Q.restore()}};q.updateCenter=function(){q.cx=Math.min(Math.max(-q.mx,q.cx),q.mx);q.cy=Math.min(Math.max(-q.my,q.cy),q.my)};q.setAutoModeTimer=function(){if(q.autoModeTimerId!=null){window.clearTimeout(q.autoModeTimerId)}q.autoModeTimerId=window.setTimeout(q.onAutoModeTimer,200)};q.onAutoModeTimer=function(){if(q.autoModeTimerId!=null){window.clearTimeout(q.autoModeTimerId);q.autoModeTimerId=null}if(q.timeList!=null&&q.now<q.timeList.length-1){++q.now;q.updateTime();q.setAutoModeTimer()}};q.updateTime=function(){if(q.timeList!=null&&q.now<q.timeList.length){var A=q.timeList[q.now];if(q.now==q.timeList.length-1){q.autoMode=true}q.nowSnap=e.getSnap(A);q.nowSnap.output();q.updateUI();var z=e.getAutoModeCount();if(z!=q.autoModeCount){q.autoModeCount=z;q.autoMode=true}if(q.autoMode){q.setAutoModeTimer()}return}q.nowSnap=null};q.updateTimeList=function(){var C;if(q.timeList!=null&&q.now<q.timeList.length){C=q.timeList[q.now]}else{C=0}q.timeList=e.getTimeList();if(q.timeList!=null&&0<q.timeList.length){var z=Math.abs(C-q.timeList[0]);q.now=0;var B=1;var E=q.timeList.length;while(B<E){var A=B++;var D=Math.abs(C-q.timeList[A]);if(D<z){z=D;q.now=A}}q.updateTime()}};var b=function(z){this.time=z;this.items=new c()};b.__name__=true;b.prototype={addItem:function(z){this.items.add(z)},paint:function(z){var A=this.items.h;var C=null;while(A!=null){var B;B=(function(E){var D;C=A[0];A=A[1];D=C;return D}(this));B.paint(z)}},output:function(){var z=this.items.h;var B=null;while(z!=null){var A;A=(function(D){var C;B=z[0];z=z[1];C=B;return C}(this));A.output()}},getTime:function(){return this.time},__class__:b};var m=function(){};m.__name__=true;m.prototype={__class__:m};var s=function(A,B,z){this.x=A;this.y=B;this.r=z;this.colorR=0;this.colorG=0;this.colorB=0;this.colorA=1};s.__name__=true;s.__interfaces__=[m];s.prototype={rgb:function(C,B,z,A){if(A==null){A=255}this.colorR=C/255;this.colorG=B/255;this.colorB=z/255;this.colorA=A/255;return this},color:function(A){var z=e.gvGetColorFromIndex(A);this.colorR=z[0];this.colorG=z[1];this.colorB=z[2];return this},getMinX:function(){return this.x-this.r},getMinY:function(){return this.y-this.r},getMaxX:function(){return this.x+this.r},getMaxY:function(){return this.y+this.r},paint:function(z){z.fillStyle=e.rgb(this.colorR,this.colorG,this.colorB,this.colorA);z.beginPath();z.arc(this.x,this.y,this.r,0,2*Math.PI,false);z.fill()},output:function(){},__class__:s};var d=function(){this.yVec=[];this.xVec=[];this.colorR=0;this.colorG=0;this.colorB=0;this.colorA=1};d.__name__=true;d.__interfaces__=[m];d.prototype={rgb:function(C,B,z,A){if(A==null){A=255}this.colorR=C/255;this.colorG=B/255;this.colorB=z/255;this.colorA=A/255;return this},color:function(A){var z=e.gvGetColorFromIndex(A);this.colorR=z[0];this.colorG=z[1];this.colorB=z[2];return this},add:function(z,A){this.xVec.push(z);this.yVec.push(A);return this},getMinX:function(){var A=Infinity;var C=0;var B=this.xVec;while(C<B.length){var z=B[C];++C;A=Math.min(A,z)}return A},getMinY:function(){var z=Infinity;var B=0;var A=this.yVec;while(B<A.length){var C=A[B];++B;z=Math.min(z,C)}return z},getMaxX:function(){var A=-Infinity;var C=0;var B=this.xVec;while(C<B.length){var z=B[C];++C;A=Math.max(A,z)}return A},getMaxY:function(){var z=-Infinity;var B=0;var A=this.yVec;while(B<A.length){var C=A[B];++B;z=Math.max(z,C)}return z},paint:function(z){var C=this.xVec.length;if(0<C){z.fillStyle=e.rgb(this.colorR,this.colorG,this.colorB,this.colorA);z.beginPath();z.moveTo(this.xVec[C-1],this.yVec[C-1]);var B=0;while(B<C){var A=B++;z.lineTo(this.xVec[A],this.yVec[A])}z.fill()}},output:function(){},__class__:d};var p=function(C,A,B,z){this.x=A;this.y=B;this.r=z;this.text=C;this.colorR=0;this.colorG=0;this.colorB=0;this.colorA=1};p.__name__=true;p.__interfaces__=[m];p.prototype={rgb:function(C,B,z,A){if(A==null){A=255}this.colorR=C/255;this.colorG=B/255;this.colorB=z/255;this.colorA=A/255;return this},color:function(A){var z=e.gvGetColorFromIndex(A);this.colorR=z[0];this.colorG=z[1];this.colorB=z[2];return this},getMinX:function(){return this.x-this.r},getMinY:function(){return this.y-this.r},getMaxX:function(){return this.x+this.r},getMaxY:function(){return this.y+this.r},paint:function(z){var A=0.02*this.r;z.save();z.translate(this.x,this.y);z.font="100px hoge";z.scale(A,A);z.fillStyle=e.rgb(this.colorR,this.colorG,this.colorB);z.textAlign="center";z.textBaseline="middle";z.fillText(this.text,0,0);z.restore()},output:function(){},__class__:p};var v=function(){};v.__name__=true;var j=function(){this.h={}};j.__name__=true;j.__interfaces__=[v];j.prototype={keys:function(){var z=[];for(var A in this.h){if(this.h.hasOwnProperty(A)){z.push(A|0)}}return k.iter(z)},__class__:j};var o=function(z){Error.call(this);this.val=z;this.message=String(z);if(Error.captureStackTrace){Error.captureStackTrace(this,o)}};o.__name__=true;o.__super__=Error;o.prototype=a(Error.prototype,{__class__:o});var l=function(){};l.__name__=true;l.getClass=function(B){if((B instanceof Array)&&B.__enum__==null){return Array}else{var z=B.__class__;if(z!=null){return z}var A=l.__nativeClassName(B);if(A!=null){return l.__resolveNativeClass(A)}return null}};l.__string_rec=function(H,E){if(H==null){return"null"}if(E.length>=5){return"<...>"}var D=typeof(H);if(D=="function"&&(H.__name__||H.__ename__)){D="object"}switch(D){case"object":if(H instanceof Array){if(H.__enum__){if(H.length==2){return H[0]}var z=H[0]+"(";E+="\t";var G=2;var C=H.length;while(G<C){var K=G++;if(K!=2){z+=","+l.__string_rec(H[K],E)}else{z+=l.__string_rec(H[K],E)}}return z+")"}var L=H.length;var N;var A="[";E+="\t";var F=0;while(F<L){var J=F++;A+=(J>0?",":"")+l.__string_rec(H[J],E)}A+="]";return A}var O;try{O=H.toString}catch(P){if(P instanceof o){P=P.val}return"???"}if(O!=null&&O!=Object.toString&&typeof(O)=="function"){var B=H.toString();if(B!="[object Object]"){return B}}var M=null;var I="{\n";E+="\t";var Q=H.hasOwnProperty!=null;for(var M in H){if(Q&&!H.hasOwnProperty(M)){continue}if(M=="prototype"||M=="__class__"||M=="__super__"||M=="__interfaces__"||M=="__properties__"){continue}if(I.length!=2){I+=", \n"}I+=E+M+" : "+l.__string_rec(H[M],E)}E=E.substring(1);I+="\n"+E+"}";return I;case"function":return"<function>";case"string":return H;default:return String(H)}};l.__interfLoop=function(F,A){if(F==null){return false}if(F==A){return true}var z=F.__interfaces__;if(z!=null){var D=0;var E=z.length;while(D<E){var B=D++;var C=z[B];if(C==A||l.__interfLoop(C,A)){return true}}}return l.__interfLoop(F.__super__,A)};l.__instanceof=function(A,z){if(z==null){return false}switch(z){case i:return(A|0)===A;case f:return typeof(A)=="number";case r:return typeof(A)=="boolean";case String:return typeof(A)=="string";case Array:return(A instanceof Array)&&A.__enum__==null;case u:return true;default:if(A!=null){if(typeof(z)=="function"){if(A instanceof z){return true}if(l.__interfLoop(l.getClass(A),z)){return true}}else{if(typeof(z)=="object"&&l.__isNativeObj(z)){if(A instanceof z){return true}}}}else{return false}if(z==w&&A.__name__!=null){return true}if(z==n&&A.__ename__!=null){return true}return A.__enum__==z}};l.__cast=function(A,z){if(l.__instanceof(A,z)){return A}else{throw new o("Cannot cast "+g.string(A)+" to "+g.string(z))}};l.__nativeClassName=function(A){var z=l.__toStr.call(A).slice(8,-1);if(z=="Object"||z=="Function"||z=="Math"||z=="JSON"){return null}return z};l.__isNativeObj=function(z){return l.__nativeClassName(z)!=null};l.__resolveNativeClass=function(z){return y[z]};String.prototype.__class__=String;String.__name__=true;Array.__name__=true;Date.prototype.__class__=Date;Date.__name__=["Date"];var i={__name__:["Int"]};var u={__name__:["Dynamic"]};var f=Number;f.__name__=["Float"];var r=Boolean;r.__ename__=["Bool"];var w={__name__:["Class"]};var n={};e.nowTime=0;e.maxTime=0;e.minX=0;e.minY=0;e.maxX=1;e.maxY=1;e.emptyFlag=true;e.snapMap=new j();e.outMap=new j();e.autoModeCount=0;e.colors=[[1,0,0],[0,1,0],[0,0,1],[1,1,0],[0,1,1],[1,0,1],[1,0.5,0],[1,0,0.5]];e.nowDragFlag=false;q.now=0;q.scale=1;q.cx=0;q.cy=0;q.mx=0;q.my=0;q.cursorX=0;q.cursorY=0;q.myMouseX=0;q.myMouseY=0;q.autoMode=false;q.autoModeCount=0;l.__toStr={}.toString;q.main()})(typeof console!="undefined"?console:{log:function(){}},typeof window!="undefined"?window:exports,typeof window!="undefined"?window:typeof global!="undefined"?global:typeof self!="undefined"?self:this);
</script>
)###";

int g_gvDefaultAlpha = 255;
struct GV_RGB {
  int r;
  int g;
  int b;
  int a;
  // Deprecated
  int toInt() const { return ((r & 255) << 16) | ((g & 255) << 8) | (b & 255); }
};

GV_RGB gvRGB(int r, int g, int b, int a = -1) {
  GV_RGB result;
  result.r = r;
  result.g = g;
  result.b = b;
  result.a = (a != -1) ? a : g_gvDefaultAlpha;
  return result;
}

GV_RGB gvRGB(int rgb) {
  return gvRGB((rgb >> 16) & 255, (rgb >> 8) & 255, rgb & 255);
}

const GV_RGB& gvColor(int i) {
  static GV_RGB colors[] = {
      gvRGB(0x000080), gvRGB(0x0000ee), gvRGB(0x008000), gvRGB(0x008080),
      gvRGB(0x0080ee), gvRGB(0x00ee00), gvRGB(0x00ee80), gvRGB(0x00eeee),
      gvRGB(0xee0000), gvRGB(0xee0080), gvRGB(0xee00ee), gvRGB(0xee8000),
      gvRGB(0xee8080), gvRGB(0xee80ee), gvRGB(0xaaaa00), gvRGB(0xaaaa80)};
  return colors[i % (int)(sizeof(colors) / sizeof(colors[0]))];
}

FILE* g_gvFile = NULL;
bool g_gvEnableFlag = true;
bool g_gvSocketConnect = false;
long g_gvNewTimeOffset = 0;
void gvSetEnable(bool enable) { g_gvEnableFlag = enable; }
void gvSetEnable(bool enable, bool& before) {
  before = g_gvEnableFlag;
  g_gvEnableFlag = enable;
}
void gvClose() {
  if (g_gvFile != NULL) {
#ifdef GV_JS
    fputs("</script>\n</head>\n<body>\n</body>\n</html>\n", g_gvFile);
#endif
    fclose(g_gvFile);
    g_gvFile = NULL;
    g_gvSocketConnect = false;
  }
}
#ifdef GV_JS
class dmyGvJsDestructor {
 public:
  ~dmyGvJsDestructor() { gvClose(); }
} dmyGvJsDestructorInstance;
#endif
void gvConnect(const char* host = "localhost", int port = 11111) {
#ifdef _WIN32
  fprintf(stderr, "gvConnect is not supported on win32.");
#else
#ifdef GV_JS
  assert(false);
#else
  gvClose();
  hostent* servhost = gethostbyname(host);
  sockaddr_in server;
  bzero(&server, sizeof(server));
  server.sin_family = AF_INET;
  bcopy(servhost->h_addr, &server.sin_addr, servhost->h_length);
  server.sin_port = htons(port);
  int s = socket(AF_INET, SOCK_STREAM, 0);
  if (0 < s) {
    int connect_ret = connect(s, (sockaddr*)&server, sizeof(server));
    if (connect_ret != -1) {
      g_gvFile = fdopen(s, "r+");
      assert(g_gvFile != NULL);
      g_gvSocketConnect = true;
    }
  }
  if (!g_gvSocketConnect) {
    fprintf(stderr, "GV Connection Error");
  }
#endif
#endif
}
void dmyGvFileInit() {
#ifdef GV_JS
  fputs(
      "<!DOCTYPE html>\n<html>\n<head>\n    <meta "
      "http-equiv=\"Content-Type\" "
      "content=\"text/html; charset=UTF-8\" />\n    <meta name=\"viewport\" "
      "content=\"width=device-width, user-scalable=no\" />\n    <title>",
      g_gvFile);
  fputs("gvc.js", g_gvFile);
  fputs("</title>\n", g_gvFile);
  // fputs(R"(<script src="/js/gvc.min.js")"></script>, g_gvFile);
  fputs(gv_js, g_gvFile);

  fputs("<script>\n", g_gvFile);
  fflush(g_gvFile);
  g_gvNewTimeOffset = ftell(g_gvFile);
#endif
}
void gvCreate(const char* path) {
  gvClose();
#ifdef _WIN32
  fopen_s(&g_gvFile, path, "w+");
#else
  g_gvFile = fopen(path, "w+");
#endif
  dmyGvFileInit();
}
void gvInit() {
  if (g_gvFile == NULL) {
#ifdef GV_JS
    gvCreate("result.html");
#else
    gvCreate("result.gv");
#endif
  }
}
void gvInput(double& turn, double& x, double& y) {
  assert(g_gvEnableFlag);
  assert(g_gvSocketConnect);
  fprintf(g_gvFile, "i\n");
  fflush(g_gvFile);
  char buf[1024];
  char* ret1 = fgets(buf, sizeof(buf), g_gvFile);
  assert(ret1 != NULL);
#ifdef _WIN32
  int ret2 = sscanf_s(buf, "%lf%lf%lf", &turn, &x, &y);
#else
  int ret2 = sscanf(buf, "%lf%lf%lf", &turn, &x, &y);
#endif
  assert(ret2 == 3);
}
void gvInput(int& turn, int& x, int& y) {
  double a, b, c;
  gvInput(a, b, c);
  turn = (int)lround(a);
  x = (int)lround(b);
  y = (int)lround(c);
}
void gvInput(int& turn, double& x, double& y) {
  double a;
  gvInput(a, x, y);
  turn = (int)lround(a);
}
void gvInput(double& turn, int& x, int& y) {
  double b, c;
  gvInput(turn, b, c);
  x = (int)lround(b);
  y = (int)lround(c);
}
void gvInput() {
  double a, b, c;
  gvInput(a, b, c);
}
void gvAutoMode() {
  assert(g_gvEnableFlag);
  assert(g_gvSocketConnect);
  fprintf(g_gvFile, "a\n");
  fflush(g_gvFile);
}
void gvCircle(double x, double y) {
  if (!g_gvEnableFlag) return;
  gvInit();
#ifdef GV_JS
  fprintf(g_gvFile, "c(%g, %g);\n", x, y);
#else
  fprintf(g_gvFile, "c %g %g\n", x, y);
#endif
  fflush(g_gvFile);
}
void gvCircle(double x, double y, double r, GV_RGB rgb) {
  if (!g_gvEnableFlag) return;
  gvInit();
#ifdef GV_JS
  fprintf(g_gvFile, "c(%g, %g, %g).rgb(%d, %d, %d, %d);\n", x, y, r, rgb.r,
          rgb.g, rgb.b, rgb.a);
#else
  fprintf(g_gvFile, "c %g %g %d %g\n", x, y, rgb.toInt(), r);
#endif
  fflush(g_gvFile);
}
void gvCircle(double x, double y, double r) {
#ifdef GV_JS
  if (!g_gvEnableFlag) return;
  gvInit();
  fprintf(g_gvFile, "c(%g, %g, %g);\n", x, y, r);
  fflush(g_gvFile);
#else
  gvCircle(x, y, r, gvRGB(0, 0, 0));
#endif
}
void gvCircle(double x, double y, GV_RGB rgb) {
  if (!g_gvEnableFlag) return;
  gvInit();
#ifdef GV_JS
  fprintf(g_gvFile, "c(%g, %g).rgb(%d, %d, %d, %d);\n", x, y, rgb.r, rgb.g,
          rgb.b, rgb.a);
#else
  fprintf(g_gvFile, "c %g %g %d\n", x, y, rgb.toInt());
#endif
  fflush(g_gvFile);
}
void gvText(double x, double y, double r, GV_RGB rgb, const char* format = "?",
            ...) {
  if (!g_gvEnableFlag) return;
  gvInit();
#ifdef GV_JS
  fprintf(g_gvFile, "t(\"");
  va_list arg;
  va_start(arg, format);
  vfprintf(g_gvFile, format, arg);
  va_end(arg);
  fprintf(g_gvFile, "\", %g, %g, %g).rgb(%d, %d, %d, %d);\n", x, y, r, rgb.r,
          rgb.g, rgb.b, rgb.a);
#else
  fprintf(g_gvFile, "t %g %g %d %g ", x, y, rgb.toInt(), r);
  va_list arg;
  va_start(arg, format);
  vfprintf(g_gvFile, format, arg);
  va_end(arg);
  fprintf(g_gvFile, "\n");
#endif
  fflush(g_gvFile);
}
void gvText(double x, double y, double r, const char* format = "?", ...) {
  if (!g_gvEnableFlag) return;
  gvInit();
#ifdef GV_JS
  fprintf(g_gvFile, "t(\"");
  va_list arg;
  va_start(arg, format);
  vfprintf(g_gvFile, format, arg);
  va_end(arg);
  fprintf(g_gvFile, "\", %g, %g, %g);\n", x, y, r);
#else
  fprintf(g_gvFile, "t %g %g 0 %g ", x, y, r);
  va_list arg;
  va_start(arg, format);
  vfprintf(g_gvFile, format, arg);
  va_end(arg);
  fprintf(g_gvFile, "\n");
#endif
  fflush(g_gvFile);
}
void gvText(double x, double y, GV_RGB rgb, const char* format = "?", ...) {
  if (!g_gvEnableFlag) return;
  gvInit();
#ifdef GV_JS
  fprintf(g_gvFile, "t(\"");
  va_list arg;
  va_start(arg, format);
  vfprintf(g_gvFile, format, arg);
  va_end(arg);
  fprintf(g_gvFile, "\", %g, %g).rgb(%d, %d, %d, %d);\n", x, y, rgb.r, rgb.g,
          rgb.b, rgb.a);
#else
  fprintf(g_gvFile, "t %g %g %d 0.5 ", x, y, rgb.toInt());
  va_list arg;
  va_start(arg, format);
  vfprintf(g_gvFile, format, arg);
  va_end(arg);
  fprintf(g_gvFile, "\n");
#endif
  fflush(g_gvFile);
}
void gvText(double x, double y, const char* format = "?", ...) {
  if (!g_gvEnableFlag) return;
  gvInit();
#ifdef GV_JS
  fprintf(g_gvFile, "t(\"");
  va_list arg;
  va_start(arg, format);
  vfprintf(g_gvFile, format, arg);
  va_end(arg);
  fprintf(g_gvFile, "\", %g, %g);\n", x, y);
#else
  fprintf(g_gvFile, "t %g %g 0 0.5 ", x, y);
  va_list arg;
  va_start(arg, format);
  vfprintf(g_gvFile, format, arg);
  va_end(arg);
  fprintf(g_gvFile, "\n");
#endif
  fflush(g_gvFile);
}
void gvImage(double x, double y, double w, double h, const char* format = "",
             ...) {
  if (!g_gvEnableFlag) return;
#ifndef GV_JS
  gvInit();
  fprintf(g_gvFile, "b %g %g %g %g ", x, y, w, h);
  va_list arg;
  va_start(arg, format);
  vfprintf(g_gvFile, format, arg);
  va_end(arg);
  fprintf(g_gvFile, "\n");
  fflush(g_gvFile);
#endif
}
void gvRect(double x, double y, double w, double h, GV_RGB rgb) {
  if (!g_gvEnableFlag) return;
  gvInit();
#ifdef GV_JS
  fprintf(g_gvFile, "p(%g, %g", x, y);
  fprintf(g_gvFile, ", %g, %g", x + w, y);
  fprintf(g_gvFile, ", %g, %g", x + w, y + h);
  fprintf(g_gvFile, ", %g, %g", x, y + h);
  fprintf(g_gvFile, ").rgb(%d, %d, %d, %d);\n", rgb.r, rgb.g, rgb.b, rgb.a);
#else
  fprintf(g_gvFile, "p %d", rgb.toInt());
  fprintf(g_gvFile, " %g %g", x, y);
  fprintf(g_gvFile, " %g %g", x + w, y);
  fprintf(g_gvFile, " %g %g", x + w, y + h);
  fprintf(g_gvFile, " %g %g", x, y + h);
  fprintf(g_gvFile, "\n");
#endif
  fflush(g_gvFile);
}
void gvRect(double x, double y, double w, double h) {
#ifdef GV_JS
  if (!g_gvEnableFlag) return;
  gvInit();
  fprintf(g_gvFile, "p(%g, %g", x, y);
  fprintf(g_gvFile, ", %g, %g", x + w, y);
  fprintf(g_gvFile, ", %g, %g", x + w, y + h);
  fprintf(g_gvFile, ", %g, %g\n", x, y + h);
  fprintf(g_gvFile, ");\n");
  fflush(g_gvFile);
#else
  gvRect(x, y, w, h, gvRGB(0, 0, 0));
#endif
}

bool g_polygon;
bool g_polygon_begin;
void gvPolygon(GV_RGB rgb, std::function<void()> f) {
  if (!g_gvEnableFlag) return;
  assert(g_polygon == false);
  g_polygon = g_polygon_begin = true;
  gvInit();
  f();
  if (!g_polygon_begin) {
    fprintf(g_gvFile, ").rgb(%d, %d, %d, %d);\n", rgb.r, rgb.g, rgb.b, rgb.a);
  }
  fflush(g_gvFile);
  g_polygon = g_polygon_begin = false;
}

void gvPolygonAdd(double x, double y) {
  if (g_polygon_begin)
    fprintf(g_gvFile, "p(%g, %g", x, y);
  else
    fprintf(g_gvFile, ", %g, %g", x, y);
  g_polygon_begin = false;
}

void gvLine(double x1, double y1, double x2, double y2, double r, GV_RGB rgb) {
  if (!g_gvEnableFlag) return;
  gvInit();
  double odx = x2 - x1;
  double ody = y2 - y1;
  double rate = r / sqrt(odx * odx + ody * ody);
  double dx = odx * rate;
  double dy = ody * rate;
#ifdef GV_JS
  fprintf(g_gvFile, "p(%g, %g", x2 - dy * (0.05 / (1 + sqrt(2))),
          y2 + dx * (0.05 / (1 + sqrt(2))));
  fprintf(g_gvFile, ", %g, %g",
          x2 - dx * (0.05 * sqrt(2) / (1 + sqrt(2))) - dy * 0.05,
          y2 - dy * (0.05 * sqrt(2) / (1 + sqrt(2))) + dx * 0.05);
  fprintf(g_gvFile, ", %g, %g",
          x1 + dx * (0.05 * sqrt(2) / (1 + sqrt(2))) - dy * 0.05,
          y1 + dy * (0.05 * sqrt(2) / (1 + sqrt(2))) + dx * 0.05);
  fprintf(g_gvFile, ", %g, %g", x1 - dy * (0.05 / (1 + sqrt(2))),
          y1 + dx * (0.05 / (1 + sqrt(2))));
  fprintf(g_gvFile, ", %g, %g", x1 + dy * (0.05 / (1 + sqrt(2))),
          y1 - dx * (0.05 / (1 + sqrt(2))));
  fprintf(g_gvFile, ", %g, %g",
          x1 + dx * (0.05 * sqrt(2) / (1 + sqrt(2))) + dy * 0.05,
          y1 + dy * (0.05 * sqrt(2) / (1 + sqrt(2))) - dx * 0.05);
  fprintf(g_gvFile, ", %g, %g",
          x2 - dx * (0.05 * sqrt(2) / (1 + sqrt(2))) + dy * 0.05,
          y2 - dy * (0.05 * sqrt(2) / (1 + sqrt(2))) - dx * 0.05);
  fprintf(g_gvFile, ", %g, %g", x2 + dy * (0.05 / (1 + sqrt(2))),
          y2 - dx * (0.05 / (1 + sqrt(2))));
  fprintf(g_gvFile, ").rgb(%d, %d, %d, %d);\n", rgb.r, rgb.g, rgb.b, rgb.a);
#else
  fprintf(g_gvFile, "p %d", rgb.toInt());
  fprintf(g_gvFile, " %g %g", x2 - dy * (0.05 / (1 + sqrt(2))),
          y2 + dx * (0.05 / (1 + sqrt(2))));
  fprintf(g_gvFile, " %g %g",
          x2 - dx * (0.05 * sqrt(2) / (1 + sqrt(2))) - dy * 0.05,
          y2 - dy * (0.05 * sqrt(2) / (1 + sqrt(2))) + dx * 0.05);
  fprintf(g_gvFile, " %g %g",
          x1 + dx * (0.05 * sqrt(2) / (1 + sqrt(2))) - dy * 0.05,
          y1 + dy * (0.05 * sqrt(2) / (1 + sqrt(2))) + dx * 0.05);
  fprintf(g_gvFile, " %g %g", x1 - dy * (0.05 / (1 + sqrt(2))),
          y1 + dx * (0.05 / (1 + sqrt(2))));
  fprintf(g_gvFile, " %g %g", x1 + dy * (0.05 / (1 + sqrt(2))),
          y1 - dx * (0.05 / (1 + sqrt(2))));
  fprintf(g_gvFile, " %g %g",
          x1 + dx * (0.05 * sqrt(2) / (1 + sqrt(2))) + dy * 0.05,
          y1 + dy * (0.05 * sqrt(2) / (1 + sqrt(2))) - dx * 0.05);
  fprintf(g_gvFile, " %g %g",
          x2 - dx * (0.05 * sqrt(2) / (1 + sqrt(2))) + dy * 0.05,
          y2 - dy * (0.05 * sqrt(2) / (1 + sqrt(2))) - dx * 0.05);
  fprintf(g_gvFile, " %g %g", x2 + dy * (0.05 / (1 + sqrt(2))),
          y2 - dx * (0.05 / (1 + sqrt(2))));
  fprintf(g_gvFile, "\n");
#endif
  fflush(g_gvFile);
}
void gvLine(double x1, double y1, double x2, double y2, double r) {
  gvLine(x1, y1, x2, y2, r, gvRGB(0, 0, 0));
}
void gvLine(double x1, double y1, double x2, double y2, GV_RGB rgb) {
  gvLine(x1, y1, x2, y2, 0.5, rgb);
}
void gvLine(double x1, double y1, double x2, double y2) {
  gvLine(x1, y1, x2, y2, 0.5);
}
double g_gvLastLineX;
double g_gvLastLineY;
void gvMoveTo(double x, double y) {
  g_gvLastLineX = x;
  g_gvLastLineY = y;
}
void gvLineTo(double x, double y, GV_RGB rgb) {
  if (!g_gvEnableFlag) return;
  gvLine(g_gvLastLineX, g_gvLastLineY, x, y, rgb);
  g_gvLastLineX = x;
  g_gvLastLineY = y;
}
void gvLineTo(double x, double y) {
  if (!g_gvEnableFlag) return;
  gvLine(g_gvLastLineX, g_gvLastLineY, x, y);
  g_gvLastLineX = x;
  g_gvLastLineY = y;
}
void gvArrow(double x1, double y1, double x2, double y2, double r, GV_RGB rgb) {
  if (!g_gvEnableFlag) return;
  gvInit();
  double odx = x2 - x1;
  double ody = y2 - y1;
  double rate = r / sqrt(odx * odx + ody * ody);
  double dx = odx * rate;
  double dy = ody * rate;
  double x2_base = x2 + dx * 0.1;
  double y2_base = y2 + dy * 0.1;
  double dx0 = dx * 0.1 * tan(M_PI * 15 / 180);
  double dy0 = dy * 0.1 * tan(M_PI * 15 / 180);
  double x2_3 = x2_base - dx * (0.1 / sin(M_PI * 15 / 180));
  double y2_3 = y2_base - dy * (0.1 / sin(M_PI * 15 / 180));
  double x2_4 = x2_3 - dx * (0.05 / tan(M_PI * 15 / 180));
  double y2_4 = y2_3 - dy * (0.05 / tan(M_PI * 15 / 180));
  double x2_5 = x2_base - dx * (1.0 * cos(M_PI * 15 / 180));
  double y2_5 = y2_base - dy * (1.0 * cos(M_PI * 15 / 180));
  double x2_6 = x2_5 - dx * (0.1 * sin(M_PI * 15 / 180));
  double y2_6 = y2_5 - dy * (0.1 * sin(M_PI * 15 / 180));
  double dx5 = dx * (1.0 * sin(M_PI * 15 / 180));
  double dy5 = dy * (1.0 * sin(M_PI * 15 / 180));
  double dx6 = dx5 - dx * (0.1 * cos(M_PI * 15 / 180));
  double dy6 = dy5 - dy * (0.1 * cos(M_PI * 15 / 180));
#ifdef GV_JS
  fprintf(g_gvFile, "p(%g, %g", x2 - dy0, y2 + dx0);
  fprintf(g_gvFile, ", %g, %g", x2_5 - dy5, y2_5 + dx5);
  fprintf(g_gvFile, ", %g, %g", x2_6 - dy6, y2_6 + dx6);
  fprintf(g_gvFile, ", %g, %g", x2_4 - dy * 0.05, y2_4 + dx * 0.05);
  fprintf(g_gvFile, ", %g, %g",
          x1 + dx * (0.05 * sqrt(2) / (1 + sqrt(2))) - dy * 0.05,
          y1 + dy * (0.05 * sqrt(2) / (1 + sqrt(2))) + dx * 0.05);
  fprintf(g_gvFile, ", %g, %g", x1 - dy * (0.05 / (1 + sqrt(2))),
          y1 + dx * (0.05 / (1 + sqrt(2))));
  fprintf(g_gvFile, ", %g, %g", x1 + dy * (0.05 / (1 + sqrt(2))),
          y1 - dx * (0.05 / (1 + sqrt(2))));
  fprintf(g_gvFile, ", %g, %g",
          x1 + dx * (0.05 * sqrt(2) / (1 + sqrt(2))) + dy * 0.05,
          y1 + dy * (0.05 * sqrt(2) / (1 + sqrt(2))) - dx * 0.05);
  fprintf(g_gvFile, ", %g, %g", x2_4 + dy * 0.05, y2_4 - dx * 0.05);
  fprintf(g_gvFile, ", %g, %g", x2_6 + dy6, y2_6 - dx6);
  fprintf(g_gvFile, ", %g, %g", x2_5 + dy5, y2_5 - dx5);
  fprintf(g_gvFile, ", %g, %g", x2 + dy0, y2 - dx0);
  fprintf(g_gvFile, ").rgb(%d, %d, %d, %d);\n", rgb.r, rgb.g, rgb.b, rgb.a);
#else
  fprintf(g_gvFile, "p %d", rgb.toInt());
  fprintf(g_gvFile, " %g %g", x2 - dy0, y2 + dx0);
  fprintf(g_gvFile, " %g %g", x2_5 - dy5, y2_5 + dx5);
  fprintf(g_gvFile, " %g %g", x2_6 - dy6, y2_6 + dx6);
  fprintf(g_gvFile, " %g %g", x2_4 - dy * 0.05, y2_4 + dx * 0.05);
  fprintf(g_gvFile, " %g %g",
          x1 + dx * (0.05 * sqrt(2) / (1 + sqrt(2))) - dy * 0.05,
          y1 + dy * (0.05 * sqrt(2) / (1 + sqrt(2))) + dx * 0.05);
  fprintf(g_gvFile, " %g %g", x1 - dy * (0.05 / (1 + sqrt(2))),
          y1 + dx * (0.05 / (1 + sqrt(2))));
  fprintf(g_gvFile, " %g %g", x1 + dy * (0.05 / (1 + sqrt(2))),
          y1 - dx * (0.05 / (1 + sqrt(2))));
  fprintf(g_gvFile, " %g %g",
          x1 + dx * (0.05 * sqrt(2) / (1 + sqrt(2))) + dy * 0.05,
          y1 + dy * (0.05 * sqrt(2) / (1 + sqrt(2))) - dx * 0.05);
  fprintf(g_gvFile, " %g %g", x2_4 + dy * 0.05, y2_4 - dx * 0.05);
  fprintf(g_gvFile, " %g %g", x2_6 + dy6, y2_6 - dx6);
  fprintf(g_gvFile, " %g %g", x2_5 + dy5, y2_5 - dx5);
  fprintf(g_gvFile, " %g %g", x2 + dy0, y2 - dx0);
  fprintf(g_gvFile, "\n");
#endif
  fflush(g_gvFile);
}
void gvArrow(double x1, double y1, double x2, double y2, double r) {
  gvArrow(x1, y1, x2, y2, r, gvRGB(0, 0, 0));
}
void gvArrow(double x1, double y1, double x2, double y2, GV_RGB rgb) {
  gvArrow(x1, y1, x2, y2, 0.5, rgb);
}
void gvArrow(double x1, double y1, double x2, double y2) {
  gvArrow(x1, y1, x2, y2, 0.5);
}
void gvArrowTo(double x, double y, double r, GV_RGB rgb) {
  if (!g_gvEnableFlag) return;
  gvArrow(g_gvLastLineX, g_gvLastLineY, x, y, r, rgb);
  g_gvLastLineX = x;
  g_gvLastLineY = y;
}
void gvArrowTo(double x, double y, double r) {
  gvArrowTo(x, y, r, gvRGB(0, 0, 0));
}
void gvArrowTo(double x, double y, GV_RGB rgb) { gvArrowTo(x, y, 0.5, rgb); }
void gvArrowTo(double x, double y) { gvArrowTo(x, y, 0.5); }
void gvArrowFrom(double x, double y, double r, GV_RGB rgb) {
  if (!g_gvEnableFlag) return;
  gvArrow(x, y, g_gvLastLineX, g_gvLastLineY, rgb);
  g_gvLastLineX = x;
  g_gvLastLineY = y;
}
void gvArrowFrom(double x, double y, double r) {
  gvArrowFrom(x, y, r, gvRGB(0, 0, 0));
}
void gvArrowFrom(double x, double y, GV_RGB rgb) {
  gvArrowFrom(x, y, 0.5, rgb);
}
void gvArrowFrom(double x, double y) { gvArrowFrom(x, y, 0.5); }
void gvArrow2(double x1, double y1, double x2, double y2, double r,
              GV_RGB rgb) {
  if (!g_gvEnableFlag) return;
  gvInit();
  double odx = x2 - x1;
  double ody = y2 - y1;
  double rate = r / sqrt(odx * odx + ody * ody);
  double dx = odx * rate;
  double dy = ody * rate;
  double x1_base = x1 - dx * 0.1;
  double y1_base = y1 - dy * 0.1;
  double x2_base = x2 + dx * 0.1;
  double y2_base = y2 + dy * 0.1;
  double dx0 = dx * 0.1 * tan(M_PI * 15 / 180);
  double dy0 = dy * 0.1 * tan(M_PI * 15 / 180);
  double x2_3 = x2_base - dx * (0.1 / sin(M_PI * 15 / 180));
  double y2_3 = y2_base - dy * (0.1 / sin(M_PI * 15 / 180));
  double x2_4 = x2_3 - dx * (0.05 / tan(M_PI * 15 / 180));
  double y2_4 = y2_3 - dy * (0.05 / tan(M_PI * 15 / 180));
  double x2_5 = x2_base - dx * (1.0 * cos(M_PI * 15 / 180));
  double y2_5 = y2_base - dy * (1.0 * cos(M_PI * 15 / 180));
  double x2_6 = x2_5 - dx * (0.1 * sin(M_PI * 15 / 180));
  double y2_6 = y2_5 - dy * (0.1 * sin(M_PI * 15 / 180));
  double x1_3 = x1_base + dx * (0.1 / sin(M_PI * 15 / 180));
  double y1_3 = y1_base + dy * (0.1 / sin(M_PI * 15 / 180));
  double x1_4 = x1_3 + dx * (0.05 / tan(M_PI * 15 / 180));
  double y1_4 = y1_3 + dy * (0.05 / tan(M_PI * 15 / 180));
  double x1_5 = x1_base + dx * (1.0 * cos(M_PI * 15 / 180));
  double y1_5 = y1_base + dy * (1.0 * cos(M_PI * 15 / 180));
  double x1_6 = x1_5 + dx * (0.1 * sin(M_PI * 15 / 180));
  double y1_6 = y1_5 + dy * (0.1 * sin(M_PI * 15 / 180));
  double dx5 = dx * (1.0 * sin(M_PI * 15 / 180));
  double dy5 = dy * (1.0 * sin(M_PI * 15 / 180));
  double dx6 = dx5 - dx * (0.1 * cos(M_PI * 15 / 180));
  double dy6 = dy5 - dy * (0.1 * cos(M_PI * 15 / 180));
#ifdef GV_JS
  fprintf(g_gvFile, "p(%g, %g", x2 - dy0, y2 + dx0);
  fprintf(g_gvFile, ", %g, %g", x2_5 - dy5, y2_5 + dx5);
  fprintf(g_gvFile, ", %g, %g", x2_6 - dy6, y2_6 + dx6);
  fprintf(g_gvFile, ", %g, %g", x2_4 - dy * 0.05, y2_4 + dx * 0.05);
  fprintf(g_gvFile, ", %g, %g", x1_4 - dy * 0.05, y1_4 + dx * 0.05);
  fprintf(g_gvFile, ", %g, %g", x1_6 - dy6, y1_6 + dx6);
  fprintf(g_gvFile, ", %g, %g", x1_5 - dy5, y1_5 + dx5);
  fprintf(g_gvFile, ", %g, %g", x1 - dy0, y1 + dx0);
  fprintf(g_gvFile, ", %g, %g", x1 + dy0, y1 - dx0);
  fprintf(g_gvFile, ", %g, %g", x1_5 + dy5, y1_5 - dx5);
  fprintf(g_gvFile, ", %g, %g", x1_6 + dy6, y1_6 - dx6);
  fprintf(g_gvFile, ", %g, %g", x1_4 + dy * 0.05, y1_4 - dx * 0.05);
  fprintf(g_gvFile, ", %g, %g", x2_4 + dy * 0.05, y2_4 - dx * 0.05);
  fprintf(g_gvFile, ", %g, %g", x2_6 + dy6, y2_6 - dx6);
  fprintf(g_gvFile, ", %g, %g", x2_5 + dy5, y2_5 - dx5);
  fprintf(g_gvFile, ", %g, %g", x2 + dy0, y2 - dx0);
  fprintf(g_gvFile, ").rgb(%d, %d, %d, %d);\n", rgb.r, rgb.g, rgb.b, rgb.a);
#else
  fprintf(g_gvFile, "p %d", rgb.toInt());
  fprintf(g_gvFile, " %g %g", x2 - dy0, y2 + dx0);
  fprintf(g_gvFile, " %g %g", x2_5 - dy5, y2_5 + dx5);
  fprintf(g_gvFile, " %g %g", x2_6 - dy6, y2_6 + dx6);
  fprintf(g_gvFile, " %g %g", x2_4 - dy * 0.05, y2_4 + dx * 0.05);
  fprintf(g_gvFile, " %g %g", x1_4 - dy * 0.05, y1_4 + dx * 0.05);
  fprintf(g_gvFile, " %g %g", x1_6 - dy6, y1_6 + dx6);
  fprintf(g_gvFile, " %g %g", x1_5 - dy5, y1_5 + dx5);
  fprintf(g_gvFile, " %g %g", x1 - dy0, y1 + dx0);
  fprintf(g_gvFile, " %g %g", x1 + dy0, y1 - dx0);
  fprintf(g_gvFile, " %g %g", x1_5 + dy5, y1_5 - dx5);
  fprintf(g_gvFile, " %g %g", x1_6 + dy6, y1_6 - dx6);
  fprintf(g_gvFile, " %g %g", x1_4 + dy * 0.05, y1_4 - dx * 0.05);
  fprintf(g_gvFile, " %g %g", x2_4 + dy * 0.05, y2_4 - dx * 0.05);
  fprintf(g_gvFile, " %g %g", x2_6 + dy6, y2_6 - dx6);
  fprintf(g_gvFile, " %g %g", x2_5 + dy5, y2_5 - dx5);
  fprintf(g_gvFile, " %g %g", x2 + dy0, y2 - dx0);
  fprintf(g_gvFile, "\n");
#endif
  fflush(g_gvFile);
}
void gvArrow2(double x1, double y1, double x2, double y2, double r) {
  gvArrow2(x1, y1, x2, y2, r, gvRGB(0, 0, 0));
}
void gvArrow2(double x1, double y1, double x2, double y2, GV_RGB rgb) {
  gvArrow2(x1, y1, x2, y2, 0.5, rgb);
}
void gvArrow2(double x1, double y1, double x2, double y2) {
  gvArrow2(x1, y1, x2, y2, 0.5);
}
void gvArrowFromTo(double x, double y, double r, GV_RGB rgb) {
  if (!g_gvEnableFlag) return;
  gvArrow2(g_gvLastLineX, g_gvLastLineY, x, y, r, rgb);
  g_gvLastLineX = x;
  g_gvLastLineY = y;
}
void gvArrowFromTo(double x, double y, double r) {
  gvArrowFromTo(x, y, r, gvRGB(0, 0, 0));
}
void gvArrowFromTo(double x, double y, GV_RGB rgb) {
  gvArrowFromTo(x, y, 0.5, rgb);
}
void gvArrowFromTo(double x, double y) { gvArrowFromTo(x, y, 0.5); }
void gvOutput(const char* format, ...) {
  if (!g_gvEnableFlag) return;
  gvInit();
#ifdef GV_JS
  fprintf(g_gvFile, "o(\"");
  va_list arg;
  va_start(arg, format);
  vfprintf(g_gvFile, format, arg);
  va_end(arg);
  fprintf(g_gvFile, "\");\n");
#else
  fprintf(g_gvFile, "o ");
  va_list arg;
  va_start(arg, format);
  vfprintf(g_gvFile, format, arg);
  va_end(arg);
  fprintf(g_gvFile, "\n");
#endif
  fflush(g_gvFile);
}
void gvNewTime(double time) {
  if (!g_gvEnableFlag) return;
  gvInit();
  g_gvNewTimeOffset = ftell(g_gvFile);
#ifdef GV_JS
  fprintf(g_gvFile, "n(%g);\n", time);
#else
  fprintf(g_gvFile, "n %g\n", time);
#endif
  fflush(g_gvFile);
}
void gvNewTime() {
  if (!g_gvEnableFlag) return;
  gvInit();
  g_gvNewTimeOffset = ftell(g_gvFile);
#ifdef GV_JS
  fprintf(g_gvFile, "n();\n");
#else
  fprintf(g_gvFile, "n\n");
#endif
  fflush(g_gvFile);
}
void gvRollback() {
  if (!g_gvEnableFlag) return;
  if (g_gvSocketConnect) {
    fprintf(g_gvFile, "r\n");
    fflush(g_gvFile);
  } else {
    ftruncate(fileno(g_gvFile), g_gvNewTimeOffset);
    fseek(g_gvFile, g_gvNewTimeOffset, SEEK_SET);
  }
}
void gvRollbackAll() {
  if (!g_gvEnableFlag) return;
  if (g_gvSocketConnect) {
    fprintf(g_gvFile, "ra\n");
    fflush(g_gvFile);
  } else {
    g_gvNewTimeOffset = 0;
    ftruncate(fileno(g_gvFile), g_gvNewTimeOffset);
    fseek(g_gvFile, g_gvNewTimeOffset, SEEK_SET);
    dmyGvFileInit();
  }
}
#else
#define gvRGB(...)
#define gvSetEnable(...)
#define gvClose(...)
#define gvConnect(...)
#define gvCreate(...)
#define gvInit(...)
#define gvInput(...)
#define gvCircle(...)
#define gvText(...)
#define gvImage(...)
#define gvRect(...)
#define gvLine(...)
#define gvArrow(...)
#define gvArrow2(...)
#define gvMoveTo(...)
#define gvLineTo(...)
#define gvOutput(...)
#define gvNewTime(...)
#define gvRollback(...)
#define gvRollbackAll(...)
#endif
