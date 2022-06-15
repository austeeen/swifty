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
   <object id="1" x="6" y="10" width="7" height="6"/>
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
   <object id="2" x="6" y="9.97826" width="7" height="6"/>
   <object id="3" x="7" y="4.97826" width="7" height="5"/>
  </objectgroup>
 </tile>
 <tile id="2">
  <objectgroup draworder="index" id="2">
   <object id="2" x="6" y="10" width="7" height="6"/>
   <object id="3" x="7" y="5" width="7" height="5"/>
  </objectgroup>
 </tile>
 <tile id="3">
  <objectgroup draworder="index" id="2">
   <object id="2" x="6" y="10" width="7" height="6"/>
   <object id="3" x="7" y="5" width="7" height="5"/>
  </objectgroup>
 </tile>
 <tile id="8" type="moving">
  <properties>
   <property name="end_early" type="int" value="0"/>
   <property name="hold_last" type="bool" value="false"/>
   <property name="one_shot" type="bool" value="false"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" x="4.04348" y="9.95652" width="10" height="6"/>
   <object id="3" x="9" y="6.91304" width="6" height="4.04348"/>
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
   <object id="3" x="4" y="10" width="10" height="6"/>
   <object id="4" x="9" y="5.93478" width="6" height="4.04348"/>
  </objectgroup>
 </tile>
 <tile id="10">
  <objectgroup draworder="index" id="2">
   <object id="3" x="4" y="10" width="10" height="6"/>
   <object id="4" x="9" y="6.8913" width="6" height="4.04348"/>
  </objectgroup>
 </tile>
 <tile id="11">
  <objectgroup draworder="index" id="2">
   <object id="3" x="4" y="9.91304" width="10" height="6"/>
   <object id="4" x="9.08696" y="5.97826" width="6" height="4.04348"/>
  </objectgroup>
 </tile>
 <tile id="12">
  <objectgroup draworder="index" id="2">
   <object id="3" x="4" y="10" width="10" height="6"/>
   <object id="4" x="8.91304" y="6.8913" width="6" height="4.04348"/>
  </objectgroup>
 </tile>
 <tile id="16" type="jump">
  <properties>
   <property name="end_early" type="int" value="2"/>
   <property name="hold_last" type="bool" value="true"/>
   <property name="one_shot" type="bool" value="true"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" x="2.95652" y="10" width="10" height="6"/>
   <object id="3" x="8.04348" y="7.02174" width="6" height="4.04348"/>
  </objectgroup>
  <animation>
   <frame tileid="0" duration="1000"/>
   <frame tileid="16" duration="60"/>
   <frame tileid="17" duration="100"/>
   <frame tileid="18" duration="300"/>
   <frame tileid="19" duration="150"/>
  </animation>
 </tile>
 <tile id="17">
  <objectgroup draworder="index" id="2">
   <object id="1" x="3.91304" y="10.9565" width="9.21743" height="5.04348"/>
   <object id="3" x="8" y="7.93478" width="6" height="4.04348"/>
  </objectgroup>
 </tile>
 <tile id="18">
  <objectgroup draworder="index" id="2">
   <object id="1" x="3.86956" y="9.94564" width="9.17395" height="5.04348"/>
   <object id="2" x="7.91305" y="6.05436" width="6" height="4.04348"/>
  </objectgroup>
 </tile>
 <tile id="19">
  <objectgroup draworder="index" id="2">
   <object id="1" x="2" y="8.0326" width="9.21743" height="5.04348"/>
   <object id="2" x="7.08696" y="6.9674" width="6" height="8"/>
  </objectgroup>
 </tile>
 <tile id="20">
  <objectgroup draworder="index" id="2">
   <object id="1" x="4" y="10.9022" width="9.00004" height="5.04348"/>
   <object id="2" x="8.08696" y="7.88044" width="6" height="4.04348"/>
  </objectgroup>
 </tile>
</tileset>
