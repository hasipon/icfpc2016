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
(function(h){var u=function(){};u.__name__=!0;u.strDate=function(a){switch(a.length){case 8:a=a.split(":");var c=new Date;c.setTime(0);c.setUTCHours(a[0]);c.setUTCMinutes(a[1]);c.setUTCSeconds(a[2]);return c;case 10:return a=a.split("-"),new Date(a[0],a[1]-1,a[2],0,0,0);case 19:return c=a.split(" "),a=c[0].split("-"),c=c[1].split(":"),new Date(a[0],a[1]-1,a[2],c[0],c[1],c[2]);default:throw"Invalid date format : "+a;}};u.iter=function(a){return{cur:0,arr:a,hasNext:function(){return this.cur<this.arr.length},
next:function(){return this.arr[this.cur++]}}};var v=function(){this.length=0};v.__name__=!0;v.prototype={add:function(a){a=[a];null==this.h?this.h=a:this.q[1]=a;this.q=a;this.length++},iterator:function(){return{h:this.h,hasNext:function(){return null!=this.h},next:function(){if(null==this.h)return null;var a=this.h[0];this.h=this.h[1];return a}}},__class__:v};var w=function(){};w.__name__=!0;Math.__name__=!0;var p=function(){};p.__name__=!0;p.string=function(a){return f.Boot.__string_rec(a,"")};
p["int"]=function(a){return a|0};var a={Gv:function(){}};a.Gv.__name__=!0;a.Gv.newTime=h.n=function(b){a.GvCore.newTime(b)};a.Gv.circle=h.c=function(b,c,d){null==d&&(d=.5);b=new a.GvSnapItem_Circle(b,c,d);a.GvCore.addItem(b);return b};a.Gv.text=h.t=function(b,c,d,e){null==e&&(e=.5);b=new a.GvSnapItem_Text(b,c,d,e);a.GvCore.addItem(b);return b};a.Gv.polygon=h.p=function(){var b=arguments,c=new a.GvSnapItem_Polygon,d=0,e;for(e=f.Boot.__cast(b.length/2,x);d<e;){var r=d++;c.add(b[2*r],b[2*r+1])}a.GvCore.addItem(c);
return c};a.Gv.line=h.l=function(b,c,d,e,r){null==r&&(r=.5);var g=new a.GvSnapItem_Polygon,l=d-b,k=e-c;r/=Math.sqrt(l*l+k*k);l*=r;k*=r;g.add(d+k*(.05/(1+Math.sqrt(2))),e+l*(.05/(1+Math.sqrt(2))));g.add(d-l*(.05*Math.sqrt(2)/(1+Math.sqrt(2)))-.05*k,e-k*(.05*Math.sqrt(2)/(1+Math.sqrt(2)))+.05*l);g.add(b+l*(.05*Math.sqrt(2)/(1+Math.sqrt(2)))-.05*k,c+k*(.05*Math.sqrt(2)/(1+Math.sqrt(2)))+.05*l);g.add(b-k*(.05/(1+Math.sqrt(2))),c+l*(.05/(1+Math.sqrt(2))));g.add(b+k*(.05/(1+Math.sqrt(2))),c-l*(.05/(1+Math.sqrt(2))));
g.add(b+l*(.05*Math.sqrt(2)/(1+Math.sqrt(2)))+.05*k,c+k*(.05*Math.sqrt(2)/(1+Math.sqrt(2)))-.05*l);g.add(d-l*(.05*Math.sqrt(2)/(1+Math.sqrt(2)))+.05*k,e-k*(.05*Math.sqrt(2)/(1+Math.sqrt(2)))-.05*l);g.add(d+k*(.05/(1+Math.sqrt(2))),e-l*(.05/(1+Math.sqrt(2))));a.GvCore.addItem(g);return g};a.Gv.out=h.o=function(b){a.GvCore.addOut(b)};a.Gv.autoMode=h.a=function(){a.GvCore.autoMode()};a.GvCore=function(){};a.GvCore.__name__=!0;a.GvCore.newTime=function(b){null==b?a.GvCore.nowTime=p["int"](.1+Math.max(0,
a.GvCore.maxTime+1)):(a.GvCore.maxTime=p["int"](.1+Math.max(a.GvCore.maxTime,b)),a.GvCore.nowTime=b)};a.GvCore.addItem=function(b){a.GvCore.emptyFlag?(a.GvCore.emptyFlag=!1,a.GvCore.minX=b.getMinX(),a.GvCore.minY=b.getMinY(),a.GvCore.maxX=b.getMaxX(),a.GvCore.maxY=b.getMaxY(),a.GvCore.maxTime=a.GvCore.nowTime):(a.GvCore.minX=Math.min(a.GvCore.minX,b.getMinX()),a.GvCore.minY=Math.min(a.GvCore.minY,b.getMinY()),a.GvCore.maxX=Math.max(a.GvCore.maxX,b.getMaxX()),a.GvCore.maxY=Math.max(a.GvCore.maxY,b.getMaxY()),
a.GvCore.maxTime=p["int"](.1+Math.max(a.GvCore.maxTime,a.GvCore.nowTime)));if(a.GvCore.snapMap.exists(a.GvCore.nowTime))a.GvCore.snapMap.get(a.GvCore.nowTime).addItem(b);else{var c=new a.GvSnap(a.GvCore.nowTime);a.GvCore.snapMap.set(a.GvCore.nowTime,c);c.addItem(b)}};a.GvCore.addOut=function(b){if(a.GvCore.outMap.exists(a.GvCore.nowTime)){var c=a.GvCore.outMap.get(a.GvCore.nowTime);a.GvCore.outMap.set(a.GvCore.nowTime,""+c+b+"\n")}else a.GvCore.outMap.set(a.GvCore.nowTime,""+b+"\n")};a.GvCore.getMinX=
function(){return a.GvCore.minX};a.GvCore.getMinY=function(){return a.GvCore.minY};a.GvCore.getMaxX=function(){return a.GvCore.maxX};a.GvCore.getMaxY=function(){return a.GvCore.maxY};a.GvCore.getTimeList=function(){for(var b=[],c=a.GvCore.snapMap.keys();c.hasNext();){var d=c.next();b.push(d)}return b};a.GvCore.getSnap=function(b){return a.GvCore.snapMap.get(b)};a.GvCore.getOut=function(b){return a.GvCore.outMap.exists(b)?a.GvCore.outMap.get(b):""};a.GvCore.getAutoModeCount=function(){return a.GvCore.autoModeCount};
a.GvCore.sendInput=function(b,c,d){if(null!=a.GvCore.inputInt_){var e=a.GvCore.inputInt_;a.GvCore.inputInt_=null;e(b,Math.round(c),Math.round(d))}else null!=a.GvCore.inputFloat_&&(e=a.GvCore.inputFloat_,a.GvCore.inputFloat_=null,e(b,c,d))};a.GvCore.gvGetColorFromIndex=function(b){return a.GvCore.colors[b]};a.GvCore.inputInt=function(b){a.GvCore.inputInt_=b;a.GvCore.inputFloat_=null};a.GvCore.inputFloat=function(b){a.GvCore.inputFloat_=b;a.GvCore.inputInt_=null};a.GvCore.setDragModeInt=function(b,
c,d){a.GvCore.dragStartInt_=b;a.GvCore.dragStartFloat_=null;a.GvCore.dragMoveInt_=c;a.GvCore.dragMoveFloat_=null;a.GvCore.dragEnd_=d};a.GvCore.setDragModeFloat=function(b,c,d){a.GvCore.dragStartInt_=b;a.GvCore.dragStartFloat_=null;a.GvCore.dragMoveInt_=c;a.GvCore.dragMoveFloat_=null;a.GvCore.dragEnd_=d};a.GvCore.isDragMode=function(){return null!=a.GvCore.dragStartInt_||null!=a.GvCore.dragStartFloat_};a.GvCore.isNowDrag=function(){return a.GvCore.nowDragFlag};a.GvCore.sendDragStart=function(b,c,d){a.GvCore.sendDragEnd();
if(null!=a.GvCore.dragStartInt_){var e=a.GvCore.dragStartInt_;a.GvCore.nowDragFlag=!0;e(b,Math.round(c),Math.round(d))}else null!=a.GvCore.dragStartFloat_&&(e=a.GvCore.dragStartFloat_,a.GvCore.nowDragFlag=!0,e(b,c,d))};a.GvCore.sendDragMove=function(b,c,d){a.GvCore.nowDragFlag&&(null!=a.GvCore.dragMoveInt_?(b=a.GvCore.dragMoveInt_,b(Math.round(c),Math.round(d))):null!=a.GvCore.dragMoveFloat_&&(b=a.GvCore.dragMoveFloat_,b(c,d)))};a.GvCore.sendDragEnd=function(){if(a.GvCore.nowDragFlag){if(null!=a.GvCore.dragEnd_){var b=
a.GvCore.dragEnd_;b()}a.GvCore.nowDragFlag=!1}};a.GvCore.autoMode=function(){++a.GvCore.autoModeCount};a.GvCore.rgb=function(a,c,d){return"rgb("+100*a+"%, "+100*c+"%, "+100*d+"%)"};a.GvMain=function(){};a.GvMain.__name__=!0;a.GvMain.main=function(){window.onload=function(b){a.GvMain.canvas=window.document.createElement("canvas");window.document.body.appendChild(a.GvMain.canvas);a.GvMain.canvas.style.position="absolute";a.GvMain.canvas.style.left="0px";a.GvMain.canvas.style.top="0px";a.GvMain.canvas.style.width=
"100%";a.GvMain.canvas.style.height="100%";a.GvMain.canvas.width=window.innerWidth;a.GvMain.canvas.height=window.innerHeight;a.GvMain.ctx=a.GvMain.canvas.getContext("2d");a.GvMain.div=window.document.createElement("pre");window.document.body.appendChild(a.GvMain.div);a.GvMain.div.style.position="absolute";a.GvMain.div.style.left="0px";a.GvMain.div.style.bottom="0px";window.onresize=function(b){a.GvMain.canvas.width=window.innerWidth;a.GvMain.canvas.height=window.innerHeight;a.GvMain.updateUI()};window.onkeydown=
function(b){switch(b.keyCode){case 33:a.GvMain.autoMode=!1;1<=a.GvMain.now&&(a.GvMain.now=p["int"](Math.max(0,a.GvMain.now-p["int"](Math.max(10,Math.sqrt(a.GvMain.timeList.length))))),a.GvMain.updateTime());break;case 34:a.GvMain.autoMode=!1;null!=a.GvMain.timeList&&a.GvMain.now<a.GvMain.timeList.length-1&&(a.GvMain.now=p["int"](Math.min(a.GvMain.now+Math.max(10,p["int"](Math.sqrt(a.GvMain.timeList.length))),a.GvMain.timeList.length-1)),a.GvMain.updateTime());break;case 35:a.GvMain.autoMode=!1;null!=
a.GvMain.timeList&&a.GvMain.now<a.GvMain.timeList.length-1&&(a.GvMain.now=a.GvMain.timeList.length-1,a.GvMain.updateTime());break;case 36:a.GvMain.autoMode=!1;1<=a.GvMain.now&&(a.GvMain.now=0,a.GvMain.updateTime());break;case 37:a.GvMain.autoMode=!1;1<=a.GvMain.now&&(--a.GvMain.now,a.GvMain.updateTime());break;case 38:a.GvMain.updateSelf(null,!1,4,!1,!1);break;case 39:a.GvMain.autoMode=!1;null!=a.GvMain.timeList&&a.GvMain.now<a.GvMain.timeList.length-1&&(++a.GvMain.now,a.GvMain.updateTime());break;
case 40:a.GvMain.updateSelf(null,!1,-4,!1,!1);break;case 97:a.GvMain.onNumpadKey(-.7,.7);break;case 98:a.GvMain.onNumpadKey(0,1);break;case 99:a.GvMain.onNumpadKey(.7,.7);break;case 100:a.GvMain.onNumpadKey(-1,0);break;case 102:a.GvMain.onNumpadKey(1,0);break;case 103:a.GvMain.onNumpadKey(-.7,-.7);break;case 104:a.GvMain.onNumpadKey(0,-1);break;case 105:a.GvMain.onNumpadKey(.7,-.7)}};var c=!1;window.onmousedown=function(b){c=!0;a.GvMain.myMouseX=b.x;a.GvMain.myMouseY=b.y;a.GvMain.updateSelf(null,
!1,0,!1,b.shiftKey);return!1};window.onmouseup=function(b){c=!1;a.GvMain.myMouseX=b.x;a.GvMain.myMouseY=b.y;a.GvMain.updateSelf(null,!1,0,!1,!1);a.GvCore.isDragMode()&&a.GvCore.isNowDrag()&&(a.GvCore.sendDragEnd(),a.GvMain.updateTimeList());return!1};window.onmousemove=function(b){a.GvMain.myMouseX=b.x;a.GvMain.myMouseY=b.y;a.GvMain.updateSelf(null,c,0,!1,!1);return!1};window.onmousewheel=function(b){a.GvMain.myMouseX=b.x;a.GvMain.myMouseY=b.y;var c;c=0<b.detail?-1:0>b.detail?1:0;0==c&&(b=b.wheelDelta,
c=0<b?1:0>b?-1:0);a.GvMain.updateSelf(null,!1,c,!1,!1);return!1};var d=null,e=null,r=0,g=0,l=12.425134878021495/Math.log(2),k=new t.ds.IntMap,f=function(b){g!=b.touches.length&&(d=null);g=b.touches.length;if(1<=b.touches.length){for(var c=0,f=b.touches.length;c<f;){var q=c++,q=b.touches.item(q);k.exists(q.identifier)||(d=null)}for(var q=f=c=0,m=b.touches.length;q<m;)var n=q++,n=b.touches.item(n),c=c+n.pageX,f=f+n.pageY;c/=b.touches.length;f/=b.touches.length;m=q=0;for(n=b.touches.length;m<n;)var p=
m++,h=b.touches.item(p),p=h.pageX-c,h=h.pageY-f,q=q+Math.sqrt(p*p+h*h+1E-5);q/=b.touches.length;null!=d?3<=b.touches.length?(a.GvMain.autoMode=!1,c=10*(c-d)/a.GvMain.canvas.width,c=r-(0<=c?Math.floor(c):Math.ceil(c)),c!=a.GvMain.now&&null!=a.GvMain.timeList&&0<=c&&c<a.GvMain.timeList.length&&(a.GvMain.now=c,a.GvMain.updateTime())):2==b.touches.length?(m=Math.log(q/e)*l,a.GvMain.myMouseX=c,a.GvMain.myMouseY=f,a.GvMain.updateSelf(null,!1,m,!1,!1),d=c,e=q):1==b.touches.length&&(a.GvMain.myMouseX=c,a.GvMain.myMouseY=
f,a.GvMain.updateSelf(null,!0,0,!1,!1),d=c,e=q):(a.GvMain.myMouseX=c,a.GvMain.myMouseY=f,a.GvMain.updateSelf(null,!1,0,!1,!1),d=c,e=q,r=a.GvMain.now)}k=new t.ds.IntMap;c=0;for(f=b.touches.length;c<f;)q=c++,q=b.touches.item(q),k.set(q.identifier,!0);b.preventDefault();return!1};window.ontouchmove=f;var n=null,m=null,h=null,A=u.strDate("2000-01-01 00:00:01").getTime()-u.strDate("2000-01-01 00:00:00").getTime();window.ontouchstart=function(b){d=null;if(1==b.touches.length){var c=b.touches.item(0).pageX,
e=b.touches.item(0).pageY,g=(new Date).getTime();if(null!=h&&g-h<=.5*A){var k=c-n,r=e-m;if(Math.sqrt(k*k+r*r)<=.05*Math.min(a.GvMain.canvas.width,a.GvMain.canvas.height))return a.GvMain.myMouseX=c,a.GvMain.myMouseY=e,a.GvMain.updateSelf(null,!1,0,!1,!0),b.preventDefault(),!1}n=c;m=e;h=g}f(b);return!1};window.ontouchcancel=function(a){d=null;a.preventDefault();return!1};window.ontouchend=function(b){d=null;b.preventDefault();b.targetTouches.length==b.touches.length&&a.GvCore.isDragMode()&&a.GvCore.isNowDrag()&&
(a.GvCore.sendDragEnd(),a.GvMain.updateTimeList());return!1};a.GvMain.updateTimeList()}};a.GvMain.onNumpadKey=function(b,c){var d=Math.min(Math.max(-a.GvMain.mx,a.GvMain.cx+b*a.GvMain.scale*.25),a.GvMain.mx),e=Math.min(Math.max(-a.GvMain.my,a.GvMain.cy+c*a.GvMain.scale*.25),a.GvMain.my);if(a.GvMain.cx!=d||a.GvMain.cy!=e)a.GvMain.cx=d,a.GvMain.cy=e,a.GvMain.updateUI()};a.GvMain.updateUI=function(){null!=a.GvMain.paintTimer&&window.clearTimeout(a.GvMain.paintTimer);a.GvMain.paintTimer=window.setTimeout(a.GvMain.paintSelf,
10)};a.GvMain.paintSelf=function(){a.GvMain.paintTimer=null;a.GvMain.updateSelf(a.GvMain.ctx,!1,0,!1,!1)};a.GvMain.updateSelf=function(b,c,d,e,f){var g=Math.max(1,a.GvMain.canvas.width),l=Math.max(1,a.GvMain.canvas.height),k=a.GvCore.getMaxX()-a.GvCore.getMinX(),h=a.GvCore.getMaxY()-a.GvCore.getMinY(),n=Math.max(k,h),m;k*l<h*g?(a.GvMain.my=.5*(1-a.GvMain.scale),m=l/(h*a.GvMain.scale),a.GvMain.mx=m*k<=g?0:(k-g/m)/n*.5):(a.GvMain.mx=.5*(1-a.GvMain.scale),m=g/(k*a.GvMain.scale),a.GvMain.my=m*h<=l?0:
(h-l/m)/n*.5);a.GvMain.updateCenter();var p=a.GvMain.cursorX,t=a.GvMain.cursorY;if(e)a.GvMain.cx=(a.GvMain.cursorX-(a.GvMain.myMouseX-.5*g)/m-.5*k-a.GvCore.getMinX())/n,a.GvMain.cy=(a.GvMain.cursorY-(a.GvMain.myMouseY-.5*l)/m-.5*h-a.GvCore.getMinY())/n,a.GvMain.updateCenter();else if(a.GvMain.cursorX=(a.GvMain.myMouseX-.5*g)/m+.5*k+a.GvCore.getMinX()+n*a.GvMain.cx,a.GvMain.cursorY=(a.GvMain.myMouseY-.5*l)/m+.5*h+a.GvCore.getMinY()+n*a.GvMain.cy,null!=a.GvMain.nowSnap){e=a.GvMain.nowSnap.getTime();
if(c)if(a.GvCore.isDragMode())a.GvCore.isNowDrag()||a.GvCore.sendDragStart(e,p,t),a.GvCore.sendDragMove(e,a.GvMain.cursorX,a.GvMain.cursorY),a.GvMain.updateTimeList();else{c=a.GvMain.cursorY-t;var t=a.GvMain.cx,u=a.GvMain.cy;a.GvMain.cx-=(a.GvMain.cursorX-p)/n;a.GvMain.cy-=c/n;a.GvMain.updateCenter();if(t!=a.GvMain.cx||u!=a.GvMain.cy){0!=d&&(a.GvMain.cursorX=(a.GvMain.myMouseX-.5*g)/m+.5*k+a.GvCore.getMinX()+n*a.GvMain.cx,a.GvMain.cursorY=(a.GvMain.myMouseY-.5*l)/m+.5*h+a.GvCore.getMinY()+n*a.GvMain.cy,
b=Math.min(Math.max(.01,a.GvMain.scale*Math.pow(.5,.080482023721841*d)),1),a.GvMain.scale!=b&&(a.GvMain.scale=b,a.GvMain.updateSelf(null,!1,0,!0,!1)));a.GvMain.updateUI();return}}if(0!=d&&(d=Math.min(Math.max(.01,a.GvMain.scale*Math.pow(.5,.080482023721841*d)),1),a.GvMain.scale!=d)){a.GvMain.scale=d;a.GvMain.updateSelf(null,!1,0,!0,!1);a.GvMain.updateUI();return}f&&(a.GvCore.sendInput(e,a.GvMain.cursorX,a.GvMain.cursorY),a.GvMain.updateTimeList());f=a.GvCore.getOut(e);0<=a.GvMain.myMouseX&&0<=a.GvMain.myMouseY&&
a.GvCore.getMinX()<=a.GvMain.cursorX&&a.GvMain.cursorX<=a.GvCore.getMaxX()&&a.GvCore.getMinY()<=a.GvMain.cursorY&&a.GvMain.cursorY<=a.GvCore.getMaxY()?a.GvMain.div.textContent=""+f+"time "+e+" ( "+(a.GvMain.now+1)+" / "+a.GvMain.timeList.length+" ) ("+(a.GvMain.cursorX+.5|0)+", "+(a.GvMain.cursorY+.5|0)+") ("+a.GvMain.cursorX+", "+a.GvMain.cursorY+")":a.GvMain.div.textContent=""+f+"time "+e+" ( "+(a.GvMain.now+1)+" / "+a.GvMain.timeList.length+" )";k=.5*(g/m-k)-a.GvCore.getMinX()-n*a.GvMain.cx;h=
.5*(l/m-h)-a.GvCore.getMinY()-n*a.GvMain.cy;null!=b&&(b.clearRect(0,0,g,l),b.save(),b.scale(m,m),b.translate(k,h),a.GvMain.nowSnap.paint(b),b.restore())}};a.GvMain.updateCenter=function(){a.GvMain.cx=Math.min(Math.max(-a.GvMain.mx,a.GvMain.cx),a.GvMain.mx);a.GvMain.cy=Math.min(Math.max(-a.GvMain.my,a.GvMain.cy),a.GvMain.my)};a.GvMain.setAutoModeTimer=function(){null!=a.GvMain.autoModeTimerId&&window.clearTimeout(a.GvMain.autoModeTimerId);a.GvMain.autoModeTimerId=window.setTimeout(a.GvMain.onAutoModeTimer,
200)};a.GvMain.onAutoModeTimer=function(){null!=a.GvMain.autoModeTimerId&&(window.clearTimeout(a.GvMain.autoModeTimerId),a.GvMain.autoModeTimerId=null);null!=a.GvMain.timeList&&a.GvMain.now<a.GvMain.timeList.length-1&&(++a.GvMain.now,a.GvMain.updateTime(),a.GvMain.setAutoModeTimer())};a.GvMain.updateTime=function(){if(null!=a.GvMain.timeList&&a.GvMain.now<a.GvMain.timeList.length){var b=a.GvMain.timeList[a.GvMain.now];a.GvMain.now==a.GvMain.timeList.length-1&&(a.GvMain.autoMode=!0);a.GvMain.nowSnap=
a.GvCore.getSnap(b);a.GvMain.nowSnap.output();a.GvMain.updateUI();b=a.GvCore.getAutoModeCount();b!=a.GvMain.autoModeCount&&(a.GvMain.autoModeCount=b,a.GvMain.autoMode=!0);a.GvMain.autoMode&&a.GvMain.setAutoModeTimer()}else a.GvMain.nowSnap=null};a.GvMain.updateTimeList=function(){var b;b=null!=a.GvMain.timeList&&a.GvMain.now<a.GvMain.timeList.length?a.GvMain.timeList[a.GvMain.now]:0;a.GvMain.timeList=a.GvCore.getTimeList();if(null!=a.GvMain.timeList&&0<a.GvMain.timeList.length){var c=Math.abs(b-a.GvMain.timeList[0]);
a.GvMain.now=0;for(var d=1,e=a.GvMain.timeList.length;d<e;){var f=d++,g=Math.abs(b-a.GvMain.timeList[f]);g<c&&(c=g,a.GvMain.now=f)}a.GvMain.updateTime()}};a.GvSnap=function(a){this.time=a;this.items=new v};a.GvSnap.__name__=!0;a.GvSnap.prototype={addItem:function(a){this.items.add(a)},paint:function(a){for(var c=this.items.iterator();c.hasNext();)c.next().paint(a)},output:function(){for(var a=this.items.iterator();a.hasNext();)a.next().output()},getTime:function(){return this.time},__class__:a.GvSnap};
a.GvSnapItem=function(){};a.GvSnapItem.__name__=!0;a.GvSnapItem.prototype={__class__:a.GvSnapItem};a.GvSnapItem_Circle=function(a,c,d){this.x=a;this.y=c;this.r=d;this.colorB=this.colorG=this.colorR=0};a.GvSnapItem_Circle.__name__=!0;a.GvSnapItem_Circle.__interfaces__=[a.GvSnapItem];a.GvSnapItem_Circle.prototype={rgb:function(a,c,d){this.colorR=a/255;this.colorG=c/255;this.colorB=d/255;return this},color:function(b){b=a.GvCore.gvGetColorFromIndex(b);this.colorR=b[0];this.colorG=b[1];this.colorB=b[2];
return this},getMinX:function(){return this.x-this.r},getMinY:function(){return this.y-this.r},getMaxX:function(){return this.x+this.r},getMaxY:function(){return this.y+this.r},paint:function(b){b.fillStyle=a.GvCore.rgb(this.colorR,this.colorG,this.colorB);b.beginPath();b.arc(this.x,this.y,this.r,0,2*Math.PI,!1);b.fill()},output:function(){},__class__:a.GvSnapItem_Circle};a.GvSnapItem_Polygon=function(){this.yVec=[];this.xVec=[];this.colorB=this.colorG=this.colorR=0};a.GvSnapItem_Polygon.__name__=
!0;a.GvSnapItem_Polygon.__interfaces__=[a.GvSnapItem];a.GvSnapItem_Polygon.prototype={rgb:function(a,c,d){this.colorR=a/255;this.colorG=c/255;this.colorB=d/255;return this},color:function(b){b=a.GvCore.gvGetColorFromIndex(b);this.colorR=b[0];this.colorG=b[1];this.colorB=b[2];return this},add:function(a,c){this.xVec.push(a);this.yVec.push(c);return this},getMinX:function(){for(var a=Math.POSITIVE_INFINITY,c=0,d=this.xVec;c<d.length;){var e=d[c];++c;a=Math.min(a,e)}return a},getMinY:function(){for(var a=
Math.POSITIVE_INFINITY,c=0,d=this.yVec;c<d.length;){var e=d[c];++c;a=Math.min(a,e)}return a},getMaxX:function(){for(var a=Math.NEGATIVE_INFINITY,c=0,d=this.xVec;c<d.length;){var e=d[c];++c;a=Math.max(a,e)}return a},getMaxY:function(){for(var a=Math.NEGATIVE_INFINITY,c=0,d=this.yVec;c<d.length;){var e=d[c];++c;a=Math.max(a,e)}return a},paint:function(b){var c=this.xVec.length;if(0<c){b.fillStyle=a.GvCore.rgb(this.colorR,this.colorG,this.colorB);b.beginPath();b.moveTo(this.xVec[c-1],this.yVec[c-1]);
for(var d=0;d<c;){var e=d++;b.lineTo(this.xVec[e],this.yVec[e])}b.fill()}},output:function(){},__class__:a.GvSnapItem_Polygon};a.GvSnapItem_Text=function(a,c,d,e){this.x=c;this.y=d;this.r=e;this.text=a;this.colorB=this.colorG=this.colorR=0};a.GvSnapItem_Text.__name__=!0;a.GvSnapItem_Text.__interfaces__=[a.GvSnapItem];a.GvSnapItem_Text.prototype={rgb:function(a,c,d){this.colorR=a/255;this.colorG=c/255;this.colorB=d/255;return this},color:function(b){b=a.GvCore.gvGetColorFromIndex(b);this.colorR=b[0];
this.colorG=b[1];this.colorB=b[2];return this},getMinX:function(){return this.x-this.r},getMinY:function(){return this.y-this.r},getMaxX:function(){return this.x+this.r},getMaxY:function(){return this.y+this.r},paint:function(b){var c=.02*this.r;b.save();b.translate(this.x,this.y);b.font="100px hoge";b.scale(c,c);b.fillStyle=a.GvCore.rgb(this.colorR,this.colorG,this.colorB);b.textAlign="center";b.textBaseline="middle";b.fillText(this.text,0,0);b.restore()},output:function(){},__class__:a.GvSnapItem_Text};
var t={ds:{}};t.ds.IntMap=function(){this.h={}};t.ds.IntMap.__name__=!0;t.ds.IntMap.__interfaces__=[w];t.ds.IntMap.prototype={set:function(a,c){this.h[a]=c},get:function(a){return this.h[a]},exists:function(a){return this.h.hasOwnProperty(a)},keys:function(){var a=[],c;for(c in this.h)this.h.hasOwnProperty(c)&&a.push(c|0);return u.iter(a)},__class__:t.ds.IntMap};var f={Boot:function(){}};f.Boot.__name__=!0;f.Boot.getClass=function(a){return a instanceof Array&&null==a.__enum__?Array:a.__class__};
f.Boot.__string_rec=function(a,c){if(null==a)return"null";if(5<=c.length)return"<...>";var d=typeof a;"function"==d&&(a.__name__||a.__ename__)&&(d="object");switch(d){case "object":if(a instanceof Array){if(a.__enum__){if(2==a.length)return a[0];d=a[0]+"(";c+="\t";for(var e=2,h=a.length;e<h;)var g=e++,d=2!=g?d+(","+f.Boot.__string_rec(a[g],c)):d+f.Boot.__string_rec(a[g],c);return d+")"}d=a.length;e="[";c+="\t";for(h=0;h<d;)g=h++,e+=(0<g?",":"")+f.Boot.__string_rec(a[g],c);return e+"]"}try{e=a.toString}catch(l){return"???"}if(null!=
e&&e!=Object.toString&&(d=a.toString(),"[object Object]"!=d))return d;d=null;e="{\n";c+="\t";h=null!=a.hasOwnProperty;for(d in a)h&&!a.hasOwnProperty(d)||"prototype"==d||"__class__"==d||"__super__"==d||"__interfaces__"==d||"__properties__"==d||(2!=e.length&&(e+=", \n"),e+=c+d+" : "+f.Boot.__string_rec(a[d],c));c=c.substring(1);return e+("\n"+c+"}");case "function":return"<function>";case "string":return a;default:return String(a)}};f.Boot.__interfLoop=function(a,c){if(null==a)return!1;if(a==c)return!0;
var d=a.__interfaces__;if(null!=d)for(var e=0,h=d.length;e<h;){var g=e++,g=d[g];if(g==c||f.Boot.__interfLoop(g,c))return!0}return f.Boot.__interfLoop(a.__super__,c)};f.Boot.__instanceof=function(a,c){if(null==c)return!1;switch(c){case x:return(a|0)===a;case y:return"number"==typeof a;case z:return"boolean"==typeof a;case String:return"string"==typeof a;case Array:return a instanceof Array&&null==a.__enum__;case B:return!0;default:if(null!=a){if("function"==typeof c&&(a instanceof c||f.Boot.__interfLoop(f.Boot.getClass(a),
c)))return!0}else return!1;return c==C&&null!=a.__name__||c==D&&null!=a.__ename__?!0:a.__enum__==c}};f.Boot.__cast=function(a,c){if(f.Boot.__instanceof(a,c))return a;throw"Cannot cast "+p.string(a)+" to "+p.string(c);};Math.NaN=Number.NaN;Math.NEGATIVE_INFINITY=Number.NEGATIVE_INFINITY;Math.POSITIVE_INFINITY=Number.POSITIVE_INFINITY;Math.isFinite=function(a){return isFinite(a)};Math.isNaN=function(a){return isNaN(a)};String.prototype.__class__=String;String.__name__=!0;Array.__name__=!0;Date.prototype.__class__=
Date;Date.__name__=["Date"];var x={__name__:["Int"]},B={__name__:["Dynamic"]},y=Number;y.__name__=["Float"];var z=Boolean;z.__ename__=["Bool"];var C={__name__:["Class"]},D={};a.GvCore.nowTime=0;a.GvCore.maxTime=0;a.GvCore.minX=0;a.GvCore.minY=0;a.GvCore.maxX=1;a.GvCore.maxY=1;a.GvCore.emptyFlag=!0;a.GvCore.snapMap=new t.ds.IntMap;a.GvCore.outMap=new t.ds.IntMap;a.GvCore.autoModeCount=0;a.GvCore.colors=[[1,0,0],[0,1,0],[0,0,1],[1,1,0],[0,1,1],[1,0,1],[1,.5,0],[1,0,.5]];a.GvCore.nowDragFlag=!1;a.GvMain.now=
0;a.GvMain.scale=1;a.GvMain.cx=0;a.GvMain.cy=0;a.GvMain.mx=0;a.GvMain.my=0;a.GvMain.cursorX=0;a.GvMain.cursorY=0;a.GvMain.myMouseX=0;a.GvMain.myMouseY=0;a.GvMain.autoMode=!1;a.GvMain.autoModeCount=0;a.GvMain.main()})("undefined"!=typeof window?window:exports);
</script>
)###";

struct GV_RGB {
  int r;
  int g;
  int b;
  int toInt() const { return ((r & 255) << 16) | ((g & 255) << 8) | (b & 255); }
};

GV_RGB gvRGB(int r, int g, int b) {
  GV_RGB result;
  result.r = r;
  result.g = g;
  result.b = b;
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
      "<!DOCTYPE html>\n<html>\n<head>\n    <meta http-equiv=\"Content-Type\" "
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
  fprintf(g_gvFile, "c(%g, %g, %g).rgb(%d, %d, %d);\n", x, y, r, rgb.r, rgb.g,
          rgb.b);
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
  fprintf(g_gvFile, "c(%g, %g).rgb(%d, %d, %d);\n", x, y, rgb.r, rgb.g, rgb.b);
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
  fprintf(g_gvFile, "\", %g, %g, %g).rgb(%d, %d, %d);\n", x, y, r, rgb.r, rgb.g,
          rgb.b);
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
  fprintf(g_gvFile, "\", %g, %g).rgb(%d, %d, %d);\n", x, y, rgb.r, rgb.g,
          rgb.b);
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
  fprintf(g_gvFile, ").rgb(%d, %d, %d);\n", rgb.r, rgb.g, rgb.b);
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
  fprintf(g_gvFile, ").rgb(%d, %d, %d);\n", rgb.r, rgb.g, rgb.b);
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
  fprintf(g_gvFile, ").rgb(%d, %d, %d);\n", rgb.r, rgb.g, rgb.b);
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
  gvArrowTo(x, y, r, gvRGB(0, 0, 0));
}
void gvArrowFrom(double x, double y, GV_RGB rgb) { gvArrowTo(x, y, 0.5, rgb); }
void gvArrowFrom(double x, double y) { gvArrowTo(x, y, 0.5); }
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
  fprintf(g_gvFile, ").rgb(%d, %d, %d);\n", rgb.r, rgb.g, rgb.b);
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
