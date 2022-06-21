<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.8" tiledversion="1.8.5" name="cat_new" tilewidth="18" tileheight="18" tilecount="30" columns="5">
 <properties>
  <property name="config" type="file" value="cat.cfg"/>
 </properties>
 <image source="elthen/cat-18x18.png" width="90" height="108"/>
 <tile id="0" type="idle">
  <properties>
   <property name="end_early" type="int" value="0"/>
   <property name="hold_last" type="bool" value="false"/>
   <property name="one_shot" type="bool" value="false"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="6.86957" y="9.04348" width="7.13043" height="5.91304"/>
   <object id="2" x="8.04348" y="3.08696" width="6.91304" height="5.91304"/>
  </objectgroup>
  <animation>
   <frame tileid="0" duration="700"/>
   <frame tileid="1" duration="120"/>
   <frame tileid="2" duration="120"/>
   <frame tileid="3" duration="120"/>
  </animation>
 </tile>
 <tile id="1">
  <objectgroup draworder="index" id="3">
   <object id="3" type="body" x="6.91305" y="9.1087" width="7.13043" height="5.91304"/>
   <object id="4" x="8.08696" y="3.15218" width="6.91304" height="5.91304"/>
  </objectgroup>
 </tile>
 <tile id="2">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="6.86957" y="9.06522" width="7.13043" height="5.91304"/>
   <object id="2" x="8.04348" y="3.1087" width="6.91304" height="5.91304"/>
  </objectgroup>
 </tile>
 <tile id="3">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="6.95653" y="9.1087" width="7.13043" height="5.91304"/>
   <object id="2" x="8.13044" y="3.15218" width="6.91304" height="5.91304"/>
  </objectgroup>
 </tile>
 <tile id="5" type="running">
  <properties>
   <property name="end_early" type="int" value="0"/>
   <property name="hold_last" type="bool" value="false"/>
   <property name="one_shot" type="bool" value="false"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4" y="10.0217" width="10.8696" height="4.86956"/>
   <object id="2" x="9.04348" y="5.89131" width="5.91304" height="4"/>
  </objectgroup>
  <animation>
   <frame tileid="7" duration="100"/>
   <frame tileid="8" duration="100"/>
   <frame tileid="9" duration="100"/>
   <frame tileid="7" duration="100"/>
   <frame tileid="6" duration="100"/>
   <frame tileid="5" duration="100"/>
  </animation>
 </tile>
 <tile id="6">
  <objectgroup draworder="index" id="5">
   <object id="7" type="body" x="4" y="9.02172" width="10.8696" height="5.86956"/>
   <object id="8" x="9.04348" y="4.89133" width="5.91304" height="4"/>
  </objectgroup>
 </tile>
 <tile id="7">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="3.91304" y="10.0217" width="10.8696" height="4.86956"/>
   <object id="2" x="8.95652" y="5.89133" width="5.91304" height="4"/>
  </objectgroup>
 </tile>
 <tile id="8">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="4.08696" y="9.02172" width="10.8696" height="5.86956"/>
   <object id="2" x="9.13044" y="4.89133" width="5.91304" height="4"/>
  </objectgroup>
 </tile>
 <tile id="9">
  <objectgroup draworder="index" id="3">
   <object id="3" type="body" x="4.08696" y="9.97824" width="10.8696" height="4.86956"/>
   <object id="4" x="9.13044" y="5.84785" width="5.91304" height="4"/>
  </objectgroup>
 </tile>
 <tile id="10" type="jumping">
  <properties>
   <property name="end_early" type="int" value="2"/>
   <property name="hold_last" type="bool" value="true"/>
   <property name="one_shot" type="bool" value="false"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="5.91304" y="8.93476" width="7.00003" height="6.13043"/>
   <object id="2" x="7.95652" y="4.02176" width="7" height="4.86957"/>
  </objectgroup>
  <animation>
   <frame tileid="10" duration="70"/>
   <frame tileid="11" duration="180"/>
   <frame tileid="12" duration="100"/>
  </animation>
 </tile>
 <tile id="11">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="5.95652" y="8.86955" width="8.17394" height="6.13043"/>
   <object id="2" x="6.91304" y="2.00002" width="7" height="6.91305"/>
  </objectgroup>
 </tile>
 <tile id="12" type="falling">
  <properties>
   <property name="end_early" type="int" value="0"/>
   <property name="hold_last" type="bool" value="true"/>
   <property name="one_shot" type="bool" value="false"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="3.86956" y="10.913" width="12.087" height="4.04347"/>
   <object id="2" x="8.95652" y="4.82611" width="7" height="6.08696"/>
  </objectgroup>
  <animation>
   <frame tileid="12" duration="180"/>
   <frame tileid="13" duration="180"/>
  </animation>
 </tile>
 <tile id="13">
  <objectgroup draworder="index" id="2">
   <object id="1" type="body" x="3.91304" y="10.1739" width="11.0435" height="4.7826"/>
   <object id="2" x="3.91304" y="6.0435" width="11.0435" height="4.04348"/>
  </objectgroup>
 </tile>
</tileset>
