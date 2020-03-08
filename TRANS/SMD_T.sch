<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.3.1">
<drawing>
<settings>
<setting alwaysvectorfont="yes"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="mm" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="burr-brown" urn="urn:adsk.eagle:library:111">
<description>&lt;b&gt;Burr-Brown Components&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="MSOP08" urn="urn:adsk.eagle:footprint:4726/1" library_version="3">
<description>&lt;b&gt;Mini Small Outline Package&lt;/b&gt;</description>
<wire x1="1.624" y1="1.299" x2="1.624" y2="-1.301" width="0.1524" layer="21"/>
<wire x1="-1.626" y1="-1.301" x2="-1.626" y2="1.299" width="0.1524" layer="21"/>
<wire x1="1.299" y1="1.624" x2="1.624" y2="1.299" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.626" y1="1.299" x2="-1.301" y2="1.624" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.626" y1="-1.301" x2="-1.301" y2="-1.626" width="0.1524" layer="21" curve="90"/>
<wire x1="1.299" y1="-1.626" x2="1.624" y2="-1.301" width="0.1524" layer="21" curve="90"/>
<wire x1="-1.341" y1="-1.626" x2="-1.204" y2="-1.626" width="0.1524" layer="21"/>
<wire x1="-0.747" y1="-1.626" x2="-0.554" y2="-1.626" width="0.1524" layer="21"/>
<wire x1="-0.097" y1="-1.626" x2="0.096" y2="-1.626" width="0.1524" layer="21"/>
<wire x1="0.553" y1="-1.626" x2="0.746" y2="-1.626" width="0.1524" layer="21"/>
<wire x1="1.203" y1="-1.626" x2="1.299" y2="-1.626" width="0.1524" layer="21"/>
<wire x1="-1.301" y1="1.624" x2="-1.204" y2="1.624" width="0.1524" layer="21"/>
<wire x1="-0.747" y1="1.624" x2="-0.554" y2="1.624" width="0.1524" layer="21"/>
<wire x1="-0.097" y1="1.624" x2="0.096" y2="1.624" width="0.1524" layer="21"/>
<wire x1="0.553" y1="1.624" x2="0.746" y2="1.624" width="0.1524" layer="21"/>
<wire x1="1.203" y1="1.624" x2="1.299" y2="1.624" width="0.1524" layer="21"/>
<circle x="-0.9456" y="-0.7906" radius="0.5" width="0.0508" layer="21"/>
<smd name="8" x="-0.976" y="2.112" dx="0.3" dy="1.2" layer="1"/>
<smd name="7" x="-0.326" y="2.112" dx="0.3" dy="1.2" layer="1"/>
<smd name="6" x="0.324" y="2.112" dx="0.3" dy="1.2" layer="1"/>
<smd name="5" x="0.974" y="2.112" dx="0.3" dy="1.2" layer="1"/>
<smd name="4" x="0.974" y="-2.113" dx="0.3" dy="1.2" layer="1"/>
<smd name="3" x="0.324" y="-2.113" dx="0.3" dy="1.2" layer="1"/>
<smd name="2" x="-0.326" y="-2.113" dx="0.3" dy="1.2" layer="1"/>
<smd name="1" x="-0.976" y="-2.113" dx="0.3" dy="1.2" layer="1"/>
<text x="-2.032" y="-2.54" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="3.302" y="-2.54" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
<rectangle x1="-1.0975" y1="1.6244" x2="-0.8537" y2="2.3557" layer="51"/>
<rectangle x1="-0.4475" y1="1.6244" x2="-0.2037" y2="2.3557" layer="51"/>
<rectangle x1="0.2025" y1="1.6244" x2="0.4463" y2="2.3557" layer="51"/>
<rectangle x1="0.8525" y1="1.6244" x2="1.0963" y2="2.3557" layer="51"/>
<rectangle x1="-1.0975" y1="-2.3569" x2="-0.8537" y2="-1.6256" layer="51"/>
<rectangle x1="-0.4475" y1="-2.3569" x2="-0.2037" y2="-1.6256" layer="51"/>
<rectangle x1="0.2025" y1="-2.3569" x2="0.4463" y2="-1.6256" layer="51"/>
<rectangle x1="0.8525" y1="-2.3569" x2="1.0963" y2="-1.6256" layer="51"/>
</package>
<package name="SO08" urn="urn:adsk.eagle:footprint:4740/1" library_version="3">
<description>&lt;b&gt;Small Outline Package&lt;/b&gt;</description>
<wire x1="-2.362" y1="-1.803" x2="2.362" y2="-1.803" width="0.1524" layer="51"/>
<wire x1="2.362" y1="-1.803" x2="2.362" y2="1.803" width="0.1524" layer="21"/>
<wire x1="2.362" y1="1.803" x2="-2.362" y2="1.803" width="0.1524" layer="51"/>
<wire x1="-2.362" y1="1.803" x2="-2.362" y2="-1.803" width="0.1524" layer="21"/>
<circle x="-1.8034" y="-0.9906" radius="0.3556" width="0.0508" layer="21"/>
<smd name="1" x="-1.905" y="-2.6162" dx="0.6096" dy="2.2098" layer="1"/>
<smd name="8" x="-1.905" y="2.6162" dx="0.6096" dy="2.2098" layer="1"/>
<smd name="2" x="-0.635" y="-2.6162" dx="0.6096" dy="2.2098" layer="1"/>
<smd name="3" x="0.635" y="-2.6162" dx="0.6096" dy="2.2098" layer="1"/>
<smd name="7" x="-0.635" y="2.6162" dx="0.6096" dy="2.2098" layer="1"/>
<smd name="6" x="0.635" y="2.6162" dx="0.6096" dy="2.2098" layer="1"/>
<smd name="4" x="1.905" y="-2.6162" dx="0.6096" dy="2.2098" layer="1"/>
<smd name="5" x="1.905" y="2.6162" dx="0.6096" dy="2.2098" layer="1"/>
<text x="4.0005" y="-2.032" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
<text x="-2.7305" y="-2.032" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<rectangle x1="-2.0828" y1="-2.8702" x2="-1.7272" y2="-1.8542" layer="51"/>
<rectangle x1="-0.8128" y1="-2.8702" x2="-0.4572" y2="-1.8542" layer="51"/>
<rectangle x1="0.4572" y1="-2.8702" x2="0.8128" y2="-1.8542" layer="51"/>
<rectangle x1="1.7272" y1="-2.8702" x2="2.0828" y2="-1.8542" layer="51"/>
<rectangle x1="-2.0828" y1="1.8542" x2="-1.7272" y2="2.8702" layer="51"/>
<rectangle x1="-0.8128" y1="1.8542" x2="-0.4572" y2="2.8702" layer="51"/>
<rectangle x1="0.4572" y1="1.8542" x2="0.8128" y2="2.8702" layer="51"/>
<rectangle x1="1.7272" y1="1.8542" x2="2.0828" y2="2.8702" layer="51"/>
</package>
</packages>
<packages3d>
<package3d name="MSOP08" urn="urn:adsk.eagle:package:4917/1" type="box" library_version="3">
<description>Mini Small Outline Package</description>
<packageinstances>
<packageinstance name="MSOP08"/>
</packageinstances>
</package3d>
<package3d name="SO08" urn="urn:adsk.eagle:package:4924/1" type="box" library_version="3">
<description>Small Outline Package</description>
<packageinstances>
<packageinstance name="SO08"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="OP-AMP+-" urn="urn:adsk.eagle:symbol:4752/1" library_version="3">
<wire x1="-3.81" y1="3.175" x2="-3.81" y2="1.905" width="0.1524" layer="94"/>
<wire x1="-4.445" y1="2.54" x2="-3.175" y2="2.54" width="0.1524" layer="94"/>
<wire x1="-4.445" y1="-2.54" x2="-3.175" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="5.08" x2="-2.54" y2="3.8862" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="-3.9116" x2="-2.54" y2="-5.08" width="0.1524" layer="94"/>
<wire x1="5.08" y1="0" x2="-5.08" y2="5.08" width="0.4064" layer="94"/>
<wire x1="-5.08" y1="5.08" x2="-5.08" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="5.08" y2="0" width="0.4064" layer="94"/>
<text x="2.54" y="5.715" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<text x="-1.27" y="4.445" size="0.8128" layer="93" rot="R90">V+</text>
<text x="-1.27" y="-5.715" size="0.8128" layer="93" rot="R90">V-</text>
<pin name="-IN" x="-7.62" y="-2.54" visible="pad" length="short" direction="in"/>
<pin name="+IN" x="-7.62" y="2.54" visible="pad" length="short" direction="in"/>
<pin name="OUT" x="7.62" y="0" visible="pad" length="short" direction="out" rot="R180"/>
<pin name="V+" x="-2.54" y="7.62" visible="pad" length="short" direction="pwr" rot="R270"/>
<pin name="V-" x="-2.54" y="-7.62" visible="pad" length="short" direction="pwr" rot="R90"/>
</symbol>
<symbol name="OP-AMP" urn="urn:adsk.eagle:symbol:4753/1" library_version="3">
<wire x1="-3.81" y1="3.175" x2="-3.81" y2="1.905" width="0.1524" layer="94"/>
<wire x1="-4.445" y1="2.54" x2="-3.175" y2="2.54" width="0.1524" layer="94"/>
<wire x1="-4.445" y1="-2.54" x2="-3.175" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="5.08" y1="0" x2="-5.08" y2="5.08" width="0.4064" layer="94"/>
<wire x1="-5.08" y1="5.08" x2="-5.08" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="5.08" y2="0" width="0.4064" layer="94"/>
<text x="2.54" y="5.715" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<pin name="-IN" x="-7.62" y="-2.54" visible="pad" length="short" direction="in"/>
<pin name="+IN" x="-7.62" y="2.54" visible="pad" length="short" direction="in"/>
<pin name="OUT" x="7.62" y="0" visible="pad" length="short" direction="out" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="OPA2237" urn="urn:adsk.eagle:component:5050/1" prefix="IC" library_version="3">
<description>&lt;b&gt;Single-Supply Operational Amplifiers&lt;/b&gt;&lt;p&gt;
MicroAmplifier(TM) Series; Product Folder:OPA2237</description>
<gates>
<gate name="A" symbol="OP-AMP+-" x="-12.7" y="0"/>
<gate name="B" symbol="OP-AMP" x="12.7" y="0"/>
</gates>
<devices>
<device name="E" package="MSOP08">
<connects>
<connect gate="A" pin="+IN" pad="3"/>
<connect gate="A" pin="-IN" pad="2"/>
<connect gate="A" pin="OUT" pad="1"/>
<connect gate="A" pin="V+" pad="8"/>
<connect gate="A" pin="V-" pad="4"/>
<connect gate="B" pin="+IN" pad="5"/>
<connect gate="B" pin="-IN" pad="6"/>
<connect gate="B" pin="OUT" pad="7"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:4917/1"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="MF" value="TEXAS INSTRUMENTS" constant="no"/>
<attribute name="MPN" value="OPA2237EA/250" constant="no"/>
<attribute name="OC_FARNELL" value="1470365" constant="no"/>
<attribute name="OC_NEWARK" value="35C1853" constant="no"/>
</technology>
</technologies>
</device>
<device name="U" package="SO08">
<connects>
<connect gate="A" pin="+IN" pad="3"/>
<connect gate="A" pin="-IN" pad="2"/>
<connect gate="A" pin="OUT" pad="1"/>
<connect gate="A" pin="V+" pad="8"/>
<connect gate="A" pin="V-" pad="4"/>
<connect gate="B" pin="+IN" pad="5"/>
<connect gate="B" pin="-IN" pad="6"/>
<connect gate="B" pin="OUT" pad="7"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:4924/1"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="MF" value="TEXAS INSTRUMENTS" constant="no"/>
<attribute name="MPN" value="OPA2237UA" constant="no"/>
<attribute name="OC_FARNELL" value="1388075" constant="no"/>
<attribute name="OC_NEWARK" value="80K6018" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="con-leotronics" urn="urn:adsk.eagle:library:160">
<description>&lt;b&gt;Connectors from Leotronics&lt;/b&gt;&lt;p&gt;
www.leotronics.co.uk&lt;br&gt;</description>
<packages>
<package name="1296-08" urn="urn:adsk.eagle:footprint:7819/1" library_version="1">
<description>&lt;b&gt;1.27mm SINGLE ROW FEMALE SOCKET&lt;/b&gt;&lt;p&gt;
Source: http://www.leotronics.co.uk/Conexcon/Data%20Sheets/sec.%20A/1296ing.pdf</description>
<wire x1="-2.159" y1="0.381" x2="-1.651" y2="0.381" width="0.1016" layer="21"/>
<wire x1="-1.651" y1="0.381" x2="-1.651" y2="0.889" width="0.1016" layer="51"/>
<wire x1="-1.651" y1="0.889" x2="-2.159" y2="0.889" width="0.1016" layer="51"/>
<wire x1="-2.159" y1="0.889" x2="-2.159" y2="0.381" width="0.1016" layer="51"/>
<wire x1="-1.397" y1="0.127" x2="-1.397" y2="1.143" width="0.1016" layer="21"/>
<wire x1="-1.397" y1="1.143" x2="-2.413" y2="1.143" width="0.1016" layer="51"/>
<wire x1="-2.413" y1="1.143" x2="-2.413" y2="0.127" width="0.1016" layer="21"/>
<wire x1="-2.413" y1="0.127" x2="-1.397" y2="0.127" width="0.1016" layer="21"/>
<wire x1="-2.159" y1="-0.889" x2="-1.651" y2="-0.889" width="0.1016" layer="51"/>
<wire x1="-1.651" y1="-0.889" x2="-1.651" y2="-0.381" width="0.1016" layer="51"/>
<wire x1="-1.651" y1="-0.381" x2="-2.159" y2="-0.381" width="0.1016" layer="21"/>
<wire x1="-2.159" y1="-0.381" x2="-2.159" y2="-0.889" width="0.1016" layer="51"/>
<wire x1="-1.397" y1="-1.143" x2="-1.397" y2="-0.127" width="0.1016" layer="21"/>
<wire x1="-1.397" y1="-0.127" x2="-2.413" y2="-0.127" width="0.1016" layer="21"/>
<wire x1="-2.413" y1="-0.127" x2="-2.413" y2="-1.143" width="0.1016" layer="21"/>
<wire x1="-2.413" y1="-1.143" x2="-1.397" y2="-1.143" width="0.1016" layer="51"/>
<wire x1="-0.889" y1="0.381" x2="-0.381" y2="0.381" width="0.1016" layer="21"/>
<wire x1="-0.381" y1="0.381" x2="-0.381" y2="0.889" width="0.1016" layer="51"/>
<wire x1="-0.381" y1="0.889" x2="-0.889" y2="0.889" width="0.1016" layer="51"/>
<wire x1="-0.889" y1="0.889" x2="-0.889" y2="0.381" width="0.1016" layer="51"/>
<wire x1="-0.127" y1="0.127" x2="-0.127" y2="1.143" width="0.1016" layer="21"/>
<wire x1="-0.127" y1="1.143" x2="-1.143" y2="1.143" width="0.1016" layer="51"/>
<wire x1="-1.143" y1="1.143" x2="-1.143" y2="0.127" width="0.1016" layer="21"/>
<wire x1="-1.143" y1="0.127" x2="-0.127" y2="0.127" width="0.1016" layer="21"/>
<wire x1="-0.889" y1="-0.889" x2="-0.381" y2="-0.889" width="0.1016" layer="51"/>
<wire x1="-0.381" y1="-0.889" x2="-0.381" y2="-0.381" width="0.1016" layer="51"/>
<wire x1="-0.381" y1="-0.381" x2="-0.889" y2="-0.381" width="0.1016" layer="21"/>
<wire x1="-0.889" y1="-0.381" x2="-0.889" y2="-0.889" width="0.1016" layer="51"/>
<wire x1="-0.127" y1="-1.143" x2="-0.127" y2="-0.127" width="0.1016" layer="21"/>
<wire x1="-0.127" y1="-0.127" x2="-1.143" y2="-0.127" width="0.1016" layer="21"/>
<wire x1="-1.143" y1="-0.127" x2="-1.143" y2="-1.143" width="0.1016" layer="21"/>
<wire x1="-1.143" y1="-1.143" x2="-0.127" y2="-1.143" width="0.1016" layer="51"/>
<wire x1="0.381" y1="0.381" x2="0.889" y2="0.381" width="0.1016" layer="21"/>
<wire x1="0.889" y1="0.381" x2="0.889" y2="0.889" width="0.1016" layer="51"/>
<wire x1="0.889" y1="0.889" x2="0.381" y2="0.889" width="0.1016" layer="51"/>
<wire x1="0.381" y1="0.889" x2="0.381" y2="0.381" width="0.1016" layer="51"/>
<wire x1="1.143" y1="0.127" x2="1.143" y2="1.143" width="0.1016" layer="21"/>
<wire x1="1.143" y1="1.143" x2="0.127" y2="1.143" width="0.1016" layer="51"/>
<wire x1="0.127" y1="1.143" x2="0.127" y2="0.127" width="0.1016" layer="21"/>
<wire x1="0.127" y1="0.127" x2="1.143" y2="0.127" width="0.1016" layer="21"/>
<wire x1="0.381" y1="-0.889" x2="0.889" y2="-0.889" width="0.1016" layer="51"/>
<wire x1="0.889" y1="-0.889" x2="0.889" y2="-0.381" width="0.1016" layer="51"/>
<wire x1="0.889" y1="-0.381" x2="0.381" y2="-0.381" width="0.1016" layer="21"/>
<wire x1="0.381" y1="-0.381" x2="0.381" y2="-0.889" width="0.1016" layer="51"/>
<wire x1="1.143" y1="-1.143" x2="1.143" y2="-0.127" width="0.1016" layer="21"/>
<wire x1="1.143" y1="-0.127" x2="0.127" y2="-0.127" width="0.1016" layer="21"/>
<wire x1="0.127" y1="-0.127" x2="0.127" y2="-1.143" width="0.1016" layer="21"/>
<wire x1="0.127" y1="-1.143" x2="1.143" y2="-1.143" width="0.1016" layer="51"/>
<wire x1="1.651" y1="0.381" x2="2.159" y2="0.381" width="0.1016" layer="21"/>
<wire x1="2.159" y1="0.381" x2="2.159" y2="0.889" width="0.1016" layer="51"/>
<wire x1="2.159" y1="0.889" x2="1.651" y2="0.889" width="0.1016" layer="51"/>
<wire x1="1.651" y1="0.889" x2="1.651" y2="0.381" width="0.1016" layer="51"/>
<wire x1="2.413" y1="0.127" x2="2.413" y2="1.143" width="0.1016" layer="21"/>
<wire x1="2.413" y1="1.143" x2="1.397" y2="1.143" width="0.1016" layer="51"/>
<wire x1="1.397" y1="1.143" x2="1.397" y2="0.127" width="0.1016" layer="21"/>
<wire x1="1.397" y1="0.127" x2="2.413" y2="0.127" width="0.1016" layer="21"/>
<wire x1="1.651" y1="-0.889" x2="2.159" y2="-0.889" width="0.1016" layer="51"/>
<wire x1="2.159" y1="-0.889" x2="2.159" y2="-0.381" width="0.1016" layer="51"/>
<wire x1="2.159" y1="-0.381" x2="1.651" y2="-0.381" width="0.1016" layer="21"/>
<wire x1="1.651" y1="-0.381" x2="1.651" y2="-0.889" width="0.1016" layer="51"/>
<wire x1="2.413" y1="-1.143" x2="2.413" y2="-0.127" width="0.1016" layer="21"/>
<wire x1="2.413" y1="-0.127" x2="1.397" y2="-0.127" width="0.1016" layer="21"/>
<wire x1="1.397" y1="-0.127" x2="1.397" y2="-1.143" width="0.1016" layer="21"/>
<wire x1="1.397" y1="-1.143" x2="2.413" y2="-1.143" width="0.1016" layer="51"/>
<wire x1="-2.7" y1="-1.45" x2="2.7" y2="-1.45" width="0.1016" layer="51"/>
<wire x1="2.7" y1="-1.45" x2="2.7" y2="1.45" width="0.1016" layer="21"/>
<wire x1="2.7" y1="1.45" x2="-2.7" y2="1.45" width="0.1016" layer="51"/>
<wire x1="-2.7" y1="1.45" x2="-2.7" y2="-1.45" width="0.1016" layer="21"/>
<smd name="1" x="-1.905" y="-1.78" dx="0.76" dy="2.05" layer="1"/>
<smd name="2" x="-1.905" y="1.78" dx="0.76" dy="2.05" layer="1"/>
<smd name="3" x="-0.635" y="-1.78" dx="0.76" dy="2.05" layer="1"/>
<smd name="4" x="-0.635" y="1.78" dx="0.76" dy="2.05" layer="1"/>
<smd name="5" x="0.635" y="-1.78" dx="0.76" dy="2.05" layer="1"/>
<smd name="6" x="0.635" y="1.78" dx="0.76" dy="2.05" layer="1"/>
<smd name="7" x="1.905" y="-1.78" dx="0.76" dy="2.05" layer="1"/>
<smd name="8" x="1.905" y="1.78" dx="0.76" dy="2.05" layer="1"/>
<text x="-3.175" y="-2.54" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="4.445" y="-2.54" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
</package>
</packages>
<packages3d>
<package3d name="1296-08" urn="urn:adsk.eagle:package:7913/1" type="box" library_version="1">
<description>1.27mm SINGLE ROW FEMALE SOCKET
Source: http://www.leotronics.co.uk/Conexcon/Data%20Sheets/sec.%20A/1296ing.pdf</description>
<packageinstances>
<packageinstance name="1296-08"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="FVAL" urn="urn:adsk.eagle:symbol:7816/1" library_version="1">
<wire x1="0.889" y1="0.889" x2="0.889" y2="-0.889" width="0.254" layer="94" curve="180" cap="flat"/>
<text x="1.905" y="-0.762" size="1.778" layer="95">&gt;NAME</text>
<text x="-0.635" y="1.905" size="1.778" layer="96">&gt;VALUE</text>
<pin name="B" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
</symbol>
<symbol name="F" urn="urn:adsk.eagle:symbol:7817/1" library_version="1">
<wire x1="0.889" y1="0.889" x2="0.889" y2="-0.889" width="0.254" layer="94" curve="180" cap="flat"/>
<text x="1.905" y="-0.762" size="1.778" layer="95">&gt;NAME</text>
<pin name="B" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="1296-T08" urn="urn:adsk.eagle:component:8003/1" prefix="X" library_version="1">
<description>&lt;b&gt;1.27mm SINGLE ROW FEMALE SOCKET&lt;/b&gt;&lt;p&gt;
Source: http://www.leotronics.co.uk/Conexcon/Data%20Sheets/sec.%20A/1296ing.pdf</description>
<gates>
<gate name="-1" symbol="FVAL" x="-2.54" y="0" addlevel="always" swaplevel="1"/>
<gate name="-2" symbol="FVAL" x="27.94" y="0" addlevel="always" swaplevel="1"/>
<gate name="-3" symbol="F" x="-2.54" y="-2.54" addlevel="always" swaplevel="1"/>
<gate name="-4" symbol="F" x="27.94" y="-2.54" addlevel="always" swaplevel="1"/>
<gate name="-5" symbol="F" x="-2.54" y="-5.08" addlevel="always" swaplevel="1"/>
<gate name="-6" symbol="F" x="27.94" y="-5.08" addlevel="always" swaplevel="1"/>
<gate name="-7" symbol="F" x="-2.54" y="-7.62" addlevel="always" swaplevel="1"/>
<gate name="-8" symbol="F" x="27.94" y="-7.62" addlevel="always" swaplevel="1"/>
</gates>
<devices>
<device name="" package="1296-08">
<connects>
<connect gate="-1" pin="B" pad="1"/>
<connect gate="-2" pin="B" pad="2"/>
<connect gate="-3" pin="B" pad="3"/>
<connect gate="-4" pin="B" pad="4"/>
<connect gate="-5" pin="B" pad="5"/>
<connect gate="-6" pin="B" pad="6"/>
<connect gate="-7" pin="B" pad="7"/>
<connect gate="-8" pin="B" pad="8"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:7913/1"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="IC2" library="burr-brown" library_urn="urn:adsk.eagle:library:111" deviceset="OPA2237" device="U" package3d_urn="urn:adsk.eagle:package:4924/1"/>
<part name="X1" library="con-leotronics" library_urn="urn:adsk.eagle:library:160" deviceset="1296-T08" device="" package3d_urn="urn:adsk.eagle:package:7913/1"/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="IC2" gate="A" x="88.9" y="60.96" smashed="yes">
<attribute name="NAME" x="91.44" y="66.675" size="1.778" layer="95"/>
<attribute name="VALUE" x="91.44" y="55.88" size="1.778" layer="96"/>
</instance>
<instance part="IC2" gate="B" x="88.9" y="43.18" smashed="yes">
<attribute name="NAME" x="91.44" y="48.895" size="1.778" layer="95"/>
<attribute name="VALUE" x="91.44" y="38.1" size="1.778" layer="96"/>
</instance>
<instance part="X1" gate="-1" x="114.3" y="53.34" smashed="yes">
<attribute name="NAME" x="116.205" y="52.578" size="1.778" layer="95"/>
<attribute name="VALUE" x="113.665" y="55.245" size="1.778" layer="96"/>
</instance>
<instance part="X1" gate="-2" x="78.74" y="45.72" smashed="yes" rot="R180">
<attribute name="NAME" x="76.835" y="46.482" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="79.375" y="43.815" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="X1" gate="-3" x="78.74" y="63.5" smashed="yes" rot="R180">
<attribute name="NAME" x="76.835" y="64.262" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="X1" gate="-4" x="78.74" y="40.64" smashed="yes" rot="R180">
<attribute name="NAME" x="76.835" y="41.402" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="X1" gate="-5" x="78.74" y="58.42" smashed="yes" rot="R180">
<attribute name="NAME" x="76.835" y="59.182" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="X1" gate="-6" x="124.46" y="43.18" smashed="yes">
<attribute name="NAME" x="126.365" y="42.418" size="1.778" layer="95"/>
</instance>
<instance part="X1" gate="-7" x="124.46" y="60.96" smashed="yes">
<attribute name="NAME" x="126.365" y="60.198" size="1.778" layer="95"/>
</instance>
<instance part="X1" gate="-8" x="114.3" y="68.58" smashed="yes">
<attribute name="NAME" x="116.205" y="67.818" size="1.778" layer="95"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="N$1" class="0">
<segment>
<pinref part="IC2" gate="A" pin="+IN"/>
<wire x1="106.68" y1="63.5" x2="81.28" y2="63.5" width="0.1524" layer="91"/>
<pinref part="X1" gate="-3" pin="B"/>
<junction x="81.28" y="63.5"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="IC2" gate="A" pin="V+"/>
<wire x1="86.36" y1="68.58" x2="111.76" y2="68.58" width="0.1524" layer="91"/>
<pinref part="X1" gate="-8" pin="B"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="IC2" gate="A" pin="V-"/>
<wire x1="111.76" y1="53.34" x2="86.36" y2="53.34" width="0.1524" layer="91"/>
<pinref part="X1" gate="-1" pin="B"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="IC2" gate="B" pin="+IN"/>
<wire x1="81.28" y1="45.72" x2="106.68" y2="45.72" width="0.1524" layer="91"/>
<pinref part="X1" gate="-2" pin="B"/>
<junction x="81.28" y="45.72"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="IC2" gate="B" pin="-IN"/>
<wire x1="106.68" y1="40.64" x2="81.28" y2="40.64" width="0.1524" layer="91"/>
<pinref part="X1" gate="-4" pin="B"/>
<junction x="81.28" y="40.64"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="IC2" gate="B" pin="OUT"/>
<wire x1="96.52" y1="43.18" x2="121.92" y2="43.18" width="0.1524" layer="91"/>
<pinref part="X1" gate="-6" pin="B"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="IC2" gate="A" pin="OUT"/>
<wire x1="96.52" y1="60.96" x2="121.92" y2="60.96" width="0.1524" layer="91"/>
<pinref part="X1" gate="-7" pin="B"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="IC2" gate="A" pin="-IN"/>
<wire x1="81.28" y1="58.42" x2="106.68" y2="58.42" width="0.1524" layer="91"/>
<pinref part="X1" gate="-5" pin="B"/>
<junction x="81.28" y="58.42"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports the association of 3D packages
with devices in libraries, schematics, and board files. Those 3D
packages will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
