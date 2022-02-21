# FIAR_Verlegeroboter
Verlegeroboter Projekt  für Eingebette Systeme - Prüft die Verlegung der Heizungsverlegung

* Wiki Page: http://wiki.hrw-fablab.de/index.php?title=FIAR
Der Floorheat Installation Assistance Robot, kurz FIAR, ist ein eigenständig fahrendes Fahrzeug, welches den zuständigen Installateur dabei unterstützt, die Fußbodenheizung fehlerfrei in die Fugen zu verlegen. Unser Roboter folgt hierfür den Schlauch und überprüft, ob die Leitung bündig mit den Gipsplatten abschließt. Falls ein Abstand zwischen Platte und Schlauch festgestellt wird,
meldet der FIAR sich akustisch und sendet eine entsprechende Nachricht via Bluetooth auf das Smartphone des Installateur. Zur Verbindung mit dem Roboter kann man eine Bluetooth Controller App nutzen. Der Installateur kann dann den Fehler begleichen und in der App bestätigen, damit der Roboter weiterfährt.

Aufgabenstellung
============
Seit den Flutkatastrophen hierzulande, u.a. dem Elbhochwasser von 2006 und der zeitaktuellen Vorfall in NRW und Rheinland-Pfalz im vergangenen Jahr und der steigenden Erderwärmung ist die Klimadebatte eines der wichtigsten Themen der Neuzeit. Um den Ausstoß vom schädlichen Stoff Kohlenstoffdioxid zu minimieren wurde hierzu eine namensgebene Steuer eingefügt, welches die Entwicklung von innovativen Technologien in allen Sektoren künstlich zu beschleunigen. Unter diesen Sektoren fällt auch die Immobilienbranche, wo speziell das Heizen einer der höchstanspruchsvollsten Aufgaben sein wird, da bspw. ältere Ölheizungen besonders viel Kohlenstoffdioxid ausstößt und somit die Nebenkosten erhöht. Abhilfe können Fußbodenheizungen (speziell in Kombination mit einer Wärmepumpe) schaffen, die im Gegensatz zu anderen herkömmlichen Heizkörpern weniger Energie braucht und somit die Heizkosten senkt. Solche Fußboden werden vor Ort von dem zuständigen Installateur verlegt. Nachdem der Schlauch in die Fugen der Gipsplatten verlegt wurde gießt man dann Beton auf den Boden um austarierte Fläche zu schaffen. Danach würde man der Estrich auf den dann verhärtetet Beton draufgießen und danach der Fußboden verlegt. Beim Verlegen des Schlauches können natürlich auch Fehler passieren, wie bspw. das dieser nur wenige Millimeter absteht. Dieser Fehler erkennt man erst, wenn der Beton erhärtet ist. Das würde heißen, dass man diese Stelle aufstemmen müsste um den Fehler anschließend zu korrigieren. Im Rahmen dieses Moduls, zum Thema "Studierende entwickeln interaktive Systeme zur Unterstützung von Mensch und Umwelt" haben wir uns folgende Aufgabe ausgesucht. Wir sollen einen Roboter entwickeln, der den Installateur dabei helfen soll bei der Erkennung. Er fährt zunächst automatisiert den Schlau ab, misst währenddessen, ob de Schlauch zu hoch ist, um sich dann akustisch zu melden und eine dementsprechende Nachricht via App auf das Smartphone des Installateurs, der den detektierten Fehler dann begleichen kann. Dieses Projekt ist eine Kooperation mit der VWS GmbH, die sich mit solchen Flächenheizungen beschäftigt, diese verkauft und wartet. 


Verwendete Hardware
============
* 1x Arduino
* 1x L293D Motorshield (https://funduinoshop.com/elektronische-module/elektromotoren-und-zubehoer/motor-shields/l293d-motorshield-fuer-arduino-uno-und-mega)
* 1x Piezo Speaker
* 1x Makeblock RGB Linefollower (https://www.robots4all.be/Me-RGB-Line-Follower-V1?Lng=en)
* 1x Lichtschranke
* 1x DC-186 Akku
* 1x Stabiles Tank Chassis / Kettenfahrzeug / Roboter Kit TK005 (https://funduinoshop.com/diy-werkstatt/bausaetze/chassis/stabiles-tank-chassis/kettenfahrzeug/roboter-kit-tk005-fuer-arduino-projekte-geeignet)
* 1x HC-05 Bluetooth Modul
