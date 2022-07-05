<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.8" tiledversion="1.8.5" name="spider" tilewidth="16" tileheight="16" tilecount="54" columns="9">
 <properties>
  <property name="config" type="file" value="spider.cfg"/>
  <property name="facing_right" type="bool" value="false"/>
 </properties>
 <image source="elthen/spider.png" width="144" height="96"/>
 <tile id="0" type="idle">
  <properties>
   <property name="end_early" type="int" value="0"/>
   <property name="hold_last" type="bool" value="false"/>
   <property name="one_shot" type="bool" value="false"/>
  </properties>
  <objectgroup draworder="index" id="3">
   <object id="2" type="body" x="4" y="9" width="9" height="6"/>
  </objectgroup>
  <animation>
   <frame tileid="0" duration="150"/>
   <frame tileid="1" duration="600"/>
   <frame tileid="2" duration="150"/>
   <frame tileid="3" duration="150"/>
   <frame tileid="4" duration="150"/>
  </animation>
 </tile>
 <tile id="1">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4" y="9" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="2">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4" y="9" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="3">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4" y="9" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="4">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4" y="9" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="9" type="running">
  <properties>
   <property name="end_early" type="int" value="0"/>
   <property name="hold_last" type="bool" value="false"/>
   <property name="one_shot" type="bool" value="false"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4" y="9" width="9" height="6"/>
  </objectgroup>
  <animation>
   <frame tileid="9" duration="100"/>
   <frame tileid="10" duration="100"/>
   <frame tileid="11" duration="100"/>
   <frame tileid="12" duration="100"/>
   <frame tileid="13" duration="100"/>
   <frame tileid="14" duration="100"/>
  </animation>
 </tile>
 <tile id="10">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4" y="9" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="11">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4" y="9" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="12">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4" y="9" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="13">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4" y="9" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="14">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4" y="9" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="18" type="jumping">
  <properties>
   <property name="end_early" type="int" value="5"/>
   <property name="hold_last" type="bool" value="true"/>
   <property name="one_shot" type="bool" value="false"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4" y="9" width="9" height="6"/>
  </objectgroup>
  <animation>
   <frame tileid="18" duration="100"/>
   <frame tileid="19" duration="100"/>
   <frame tileid="20" duration="100"/>
   <frame tileid="21" duration="100"/>
   <frame tileid="22" duration="100"/>
  </animation>
 </tile>
 <tile id="19">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4" y="9" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="20">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4" y="10" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="21">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="2" y="4" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="22">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="2" y="3" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="23" type="falling">
  <properties>
   <property name="end_early" type="int" value="0"/>
   <property name="hold_last" type="bool" value="false"/>
   <property name="one_shot" type="bool" value="false"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="2" y="5" width="9" height="6"/>
  </objectgroup>
  <animation>
   <frame tileid="23" duration="150"/>
   <frame tileid="24" duration="150"/>
   <frame tileid="25" duration="150"/>
   <frame tileid="26" duration="150"/>
  </animation>
 </tile>
 <tile id="24">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="2" y="10" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="25">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="2" y="9" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="26">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="2" y="9" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="36" type="damaged">
  <properties>
   <property name="end_early" type="int" value="0"/>
   <property name="hold_last" type="bool" value="false"/>
   <property name="one_shot" type="bool" value="true"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4" y="9" width="9" height="6"/>
  </objectgroup>
  <animation>
   <frame tileid="36" duration="100"/>
   <frame tileid="37" duration="250"/>
   <frame tileid="38" duration="150"/>
  </animation>
 </tile>
 <tile id="37">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4" y="10" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="38">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4" y="9" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="45" type="dead">
  <properties>
   <property name="end_early" type="int" value="0"/>
   <property name="hold_last" type="bool" value="false"/>
   <property name="one_shot" type="bool" value="true"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4" y="9" width="9" height="6"/>
  </objectgroup>
  <animation>
   <frame tileid="45" duration="150"/>
   <frame tileid="46" duration="150"/>
   <frame tileid="47" duration="150"/>
   <frame tileid="48" duration="150"/>
   <frame tileid="49" duration="150"/>
   <frame tileid="50" duration="150"/>
   <frame tileid="51" duration="150"/>
   <frame tileid="52" duration="150"/>
   <frame tileid="53" duration="150"/>
  </animation>
 </tile>
 <tile id="46">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="5" y="10" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="47">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="5" y="10" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="48">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="6" y="10" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="49">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="6" y="10" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="50">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="6" y="10" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="51">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="6" y="10" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="52">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="6" y="10" width="9" height="6"/>
  </objectgroup>
 </tile>
 <tile id="53">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="6" y="10" width="9" height="6"/>
  </objectgroup>
 </tile>
</tileset>
