<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.8" tiledversion="1.8.5" name="cat" tilewidth="16" tileheight="16" tilecount="56" columns="8">
 <properties>
  <property name="config" type="file" value="res/cat.cfg"/>
 </properties>
 <image source="elthen/cat-16x16.png" width="128" height="112"/>
 <tile id="0" type="idle">
  <properties>
   <property name="end_early" type="int" value="0"/>
   <property name="hold_last" type="bool" value="false"/>
   <property name="one_shot" type="bool" value="false"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="6" y="10" width="7" height="6"/>
   <object id="2" x="7" y="5" width="7" height="5"/>
  </objectgroup>
  <animation>
   <frame tileid="0" duration="1500"/>
   <frame tileid="1" duration="100"/>
   <frame tileid="2" duration="100"/>
   <frame tileid="3" duration="100"/>
  </animation>
 </tile>
 <tile id="1">
  <objectgroup draworder="index" id="2">
   <object id="2" type="body" x="6" y="10" width="7" height="6"/>
   <object id="3" x="7" y="5" width="7" height="5"/>
  </objectgroup>
 </tile>
 <tile id="2">
  <objectgroup draworder="index" id="2">
   <object id="2" type="body" x="6" y="10" width="7" height="6"/>
   <object id="3" x="7" y="5" width="7" height="5"/>
  </objectgroup>
 </tile>
 <tile id="3">
  <objectgroup draworder="index" id="2">
   <object id="2" type="body" x="6" y="10" width="7" height="6"/>
   <object id="3" x="7" y="5" width="7" height="5"/>
  </objectgroup>
 </tile>
 <tile id="8" type="running">
  <properties>
   <property name="end_early" type="int" value="0"/>
   <property name="hold_last" type="bool" value="false"/>
   <property name="one_shot" type="bool" value="false"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4" y="10" width="10" height="6"/>
   <object id="3" x="9" y="7" width="6" height="4"/>
  </objectgroup>
  <animation>
   <frame tileid="8" duration="100"/>
   <frame tileid="9" duration="100"/>
   <frame tileid="10" duration="100"/>
   <frame tileid="11" duration="100"/>
   <frame tileid="12" duration="100"/>
  </animation>
 </tile>
 <tile id="9">
  <objectgroup draworder="index" id="2">
   <object id="3" type="body" x="4" y="10" width="10" height="6"/>
   <object id="4" x="9" y="6" width="6" height="4"/>
  </objectgroup>
 </tile>
 <tile id="10">
  <objectgroup draworder="index" id="2">
   <object id="3" type="body" x="4" y="10" width="10" height="6"/>
   <object id="4" x="9" y="7" width="6" height="4"/>
  </objectgroup>
 </tile>
 <tile id="11">
  <objectgroup draworder="index" id="2">
   <object id="3" type="body" x="4" y="10" width="10" height="6"/>
   <object id="4" x="9" y="6" width="6" height="4"/>
  </objectgroup>
 </tile>
 <tile id="12">
  <objectgroup draworder="index" id="2">
   <object id="3" type="body" x="4" y="10" width="10" height="6"/>
   <object id="4" x="9" y="7" width="6" height="4"/>
  </objectgroup>
 </tile>
 <tile id="16" type="jumping">
  <properties>
   <property name="end_early" type="int" value="2"/>
   <property name="hold_last" type="bool" value="true"/>
   <property name="one_shot" type="bool" value="false"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="3" y="10" width="10" height="6"/>
   <object id="3" x="8" y="7" width="6" height="4"/>
  </objectgroup>
  <animation>
   <frame tileid="17" duration="50"/>
   <frame tileid="26" duration="200"/>
   <frame tileid="18" duration="70"/>
  </animation>
 </tile>
 <tile id="17">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4" y="11" width="9" height="5"/>
   <object id="3" x="8" y="8" width="6" height="4"/>
  </objectgroup>
 </tile>
 <tile id="18">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4" y="10" width="9" height="5"/>
   <object id="2" x="8" y="6" width="6" height="4"/>
  </objectgroup>
 </tile>
 <tile id="19">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="2" y="8" width="5" height="5"/>
   <object id="2" type="body" x="7" y="7" width="6" height="7"/>
  </objectgroup>
 </tile>
 <tile id="20" type="falling">
  <properties>
   <property name="end_early" type="int" value="0"/>
   <property name="hold_last" type="bool" value="true"/>
   <property name="one_shot" type="bool" value="false"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4" y="11" width="9.00004" height="5"/>
   <object id="2" x="8" y="8" width="6" height="4"/>
  </objectgroup>
  <animation>
   <frame tileid="20" duration="70"/>
   <frame tileid="19" duration="250"/>
   <frame tileid="27" duration="500"/>
  </animation>
 </tile>
 <tile id="26">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4" y="7" width="8" height="6"/>
   <object id="2" x="8" y="3" width="6" height="4"/>
  </objectgroup>
 </tile>
 <tile id="27">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="3" y="5" width="5" height="5"/>
   <object id="2" type="body" x="8" y="5" width="6" height="8"/>
  </objectgroup>
 </tile>
</tileset>
