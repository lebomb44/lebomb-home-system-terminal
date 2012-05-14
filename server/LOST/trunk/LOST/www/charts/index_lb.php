<!DOCTYPE html>
<html>
<head>
  <meta http-equiv="content-type" content="text/html; charset=utf-8" />
  <title>Temperature des Chambres</title>
<?php
// http://www.highcharts.com/stock/demo/
// http://dygraphs.com/tests/range-selector.html
//[{name: 'Curve 1',data: [[1,2],[3,4],[5,6],[7,8],[9,0]]},{name: 'Curve 2',data: [[1,12],[3,14],[5,16],[7,18],[9,10]]}]
//data: [[new Date(2012,4,04,14,56,49),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,27.0,24.8],[new Date(2012,4,04,14,41,49),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,27.3,25.1],[new Date(2012,4,04,14,26,49),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,27.3,25.1],[new Date(2012,4,04,14,11,49),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,27.3,25.1],[new Date(2012,4,04,13,56,49),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,27.5,25.1],[new Date(2012,4,04,13,41,49),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,27.5,25.4],[new Date(2012,4,04,13,26,48),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,27.5,25.4],[new Date(2012,4,04,13,11,48),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,27.3,25.1],[new Date(2012,4,04,12,56,48),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,27.3,25.1],[new Date(2012,4,04,12,41,48),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,27.3,25.1],[new Date(2012,4,04,12,26,48),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,27.3,25.1],[new Date(2012,4,04,12,11,48),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,27.3,25.1],[new Date(2012,4,04,11,56,48),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,27.0,25.1],[new Date(2012,4,04,05,11,43),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.2,23.7],[new Date(2012,4,04,11,41,48),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,27.0,25.1],[new Date(2012,4,04,11,26,47),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,27.0,25.1],[new Date(2012,4,04,11,11,47),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,27.3,25.1],[new Date(2012,4,04,10,56,47),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,27.0,24.8],[new Date(2012,4,04,10,41,47),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,27.0,24.8],[new Date(2012,4,04,10,26,47),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.7,24.5],[new Date(2012,4,04,10,11,47),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.7,24.5],[new Date(2012,4,04,09,56,47),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.7,24.5],[new Date(2012,4,04,09,41,46),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.4,24.3],[new Date(2012,4,04,09,26,46),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.4,24.0],[new Date(2012,4,04,09,11,46),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.4,24.0],[new Date(2012,4,04,08,56,46),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.4,23.7],[new Date(2012,4,04,08,41,46),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.2,23.5],[new Date(2012,4,04,08,26,46),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.2,23.5],[new Date(2012,4,04,08,11,46),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,25.9,23.5],[new Date(2012,4,04,07,56,46),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,25.9,23.5],[new Date(2012,4,04,07,41,45),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,25.9,23.2],[new Date(2012,4,04,07,26,45),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,25.9,23.2],[new Date(2012,4,04,07,11,45),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,25.9,23.5],[new Date(2012,4,04,06,56,45),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,25.9,23.5],[new Date(2012,4,04,06,41,45),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,25.9,23.5],[new Date(2012,4,04,06,26,45),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,25.9,23.5],[new Date(2012,4,04,06,11,44),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,25.9,23.5],[new Date(2012,4,04,05,56,43),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,25.9,23.7],[new Date(2012,4,04,05,41,43),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,25.9,23.7],[new Date(2012,4,04,05,26,43),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,25.9,23.7],[new Date(2012,4,04,04,56,43),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.2,23.7],[new Date(2012,4,04,04,41,43),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.2,24.0],[new Date(2012,4,04,04,26,43),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.2,24.0],[new Date(2012,4,04,04,11,43),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.2,24.0],[new Date(2012,4,04,03,56,42),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.2,24.0],[new Date(2012,4,04,03,41,42),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.4,24.0],[new Date(2012,4,04,03,26,42),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.4,24.0],[new Date(2012,4,04,03,11,42),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.4,24.0],[new Date(2012,4,04,02,56,42),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.4,24.0],[new Date(2012,4,04,02,41,42),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.4,24.0],[new Date(2012,4,04,02,26,42),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.4,24.0],[new Date(2012,4,04,02,11,42),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.4,24.3],[new Date(2012,4,04,01,56,42),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.7,24.3],[new Date(2012,4,04,01,41,41),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.7,24.3],[new Date(2012,4,04,01,26,41),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.7,24.3],[new Date(2012,4,04,01,11,41),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.7,24.5],[new Date(2012,4,04,00,56,41),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,27.0,24.8],[new Date(2012,4,04,00,41,41),-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,-17.0,26.7,24.8],[new Date(2012,4,04,15,11,49),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,27.0,24.8],[new Date(2012,4,04,15,26,49),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,27.0,24.8],[new Date(2012,4,04,15,41,50),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,27.0,24.8],[new Date(2012,4,04,15,56,50),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,27.0,24.8],[new Date(2012,4,04,16,11,50),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,27.0,24.8],[new Date(2012,4,04,16,26,50),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,27.0,24.5],[new Date(2012,4,04,16,41,50),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,27.0,24.5],[new Date(2012,4,04,16,56,50),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,27.0,24.5],[new Date(2012,4,04,17,11,50),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,27.0,24.3],[new Date(2012,4,04,17,26,51),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,27.0,24.3],[new Date(2012,4,04,17,41,51),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,27.0,24.3],[new Date(2012,4,04,17,56,51),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,27.0,24.5],[new Date(2012,4,04,18,11,51),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,27.0,24.5],[new Date(2012,4,04,18,26,51),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,26.7,24.5],[new Date(2012,4,04,18,41,51),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.9,24.0],[new Date(2012,4,04,18,56,51),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,23.2],[new Date(2012,4,04,19,11,51),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.6],[new Date(2012,4,04,19,26,52),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.1,22.6],[new Date(2012,4,04,19,41,52),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.9,22.6],[new Date(2012,4,04,19,56,52),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,26.2,23.2],[new Date(2012,4,04,20,11,52),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,26.2,23.2],[new Date(2012,4,04,20,26,52),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,26.2,23.4],[new Date(2012,4,04,20,41,52),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,26.2,23.4],[new Date(2012,4,04,20,56,52),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,26.2,23.4],[new Date(2012,4,04,21,11,52),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,26.2,23.4],[new Date(2012,4,04,21,26,53),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,26.2,23.4],[new Date(2012,4,04,21,41,53),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,26.2,23.4],[new Date(2012,4,04,21,56,56),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,26.2,23.4],[new Date(2012,4,04,22,11,56),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,26.2,23.4],[new Date(2012,4,04,22,26,56),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,26.2,23.4],[new Date(2012,4,04,22,41,56),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,26.2,23.4],[new Date(2012,4,04,22,56,56),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,26.2,23.4],[new Date(2012,4,04,23,11,56),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,26.2,23.4],[new Date(2012,4,04,23,26,57),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.9,23.4],[new Date(2012,4,04,23,41,57),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.9,23.4],[new Date(2012,4,04,23,56,57),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.9,23.4],[new Date(2012,4,05,00,11,57),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.9,23.4],[new Date(2012,4,05,00,26,57),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.9,23.4],[new Date(2012,4,05,00,41,57),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.9,23.4],[new Date(2012,4,05,00,56,57),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.9,23.4],[new Date(2012,4,05,01,11,57),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.9,23.2],[new Date(2012,4,05,01,26,58),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.9,23.4],[new Date(2012,4,05,01,41,58),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.9,23.4],[new Date(2012,4,05,01,56,58),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.9,23.2],[new Date(2012,4,05,02,11,58),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,23.2],[new Date(2012,4,05,02,26,58),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,23.2],[new Date(2012,4,05,02,41,58),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,23.2],[new Date(2012,4,05,02,56,58),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,23.2],[new Date(2012,4,05,03,11,58),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,23.2],[new Date(2012,4,05,03,26,59),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.9],[new Date(2012,4,05,03,41,59),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.9],[new Date(2012,4,05,03,56,59),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.9],[new Date(2012,4,05,04,11,59),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.9],[new Date(2012,4,05,04,26,59),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.9],[new Date(2012,4,05,04,41,59),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,04,56,59),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,05,11,59),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,05,27,00),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.6],[new Date(2012,4,05,05,42,00),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.6],[new Date(2012,4,05,05,57,00),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.6],[new Date(2012,4,05,06,12,00),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.6],[new Date(2012,4,05,06,27,01),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.6],[new Date(2012,4,05,06,42,01),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.6],[new Date(2012,4,05,06,57,01),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.6],[new Date(2012,4,05,07,12,02),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.4],[new Date(2012,4,05,07,27,02),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.4],[new Date(2012,4,05,07,42,02),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.1,22.4],[new Date(2012,4,05,07,57,02),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.4],[new Date(2012,4,05,08,12,02),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.1,22.4],[new Date(2012,4,05,08,27,02),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.1,22.1],[new Date(2012,4,05,08,42,02),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.1,22.1],[new Date(2012,4,05,08,57,02),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.1,22.1],[new Date(2012,4,05,09,12,03),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.1,22.1],[new Date(2012,4,05,09,27,03),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.1,22.1],[new Date(2012,4,05,09,42,03),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.1,22.1],[new Date(2012,4,05,09,57,03),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.1,22.1],[new Date(2012,4,05,10,12,03),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.1,22.4],[new Date(2012,4,05,10,27,03),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.1,22.4],[new Date(2012,4,05,10,42,03),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.1,22.4],[new Date(2012,4,05,10,57,03),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.4],[new Date(2012,4,05,11,12,04),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.1,22.4],[new Date(2012,4,05,11,27,04),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.1,22.1],[new Date(2012,4,05,11,42,04),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.1,22.4],[new Date(2012,4,05,11,57,04),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.1,22.4],[new Date(2012,4,05,12,12,04),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.1,22.4],[new Date(2012,4,05,12,27,04),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.1,22.4],[new Date(2012,4,05,12,42,04),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.4],[new Date(2012,4,05,12,57,04),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.4],[new Date(2012,4,05,13,12,05),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.4],[new Date(2012,4,05,13,27,05),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.4],[new Date(2012,4,05,13,42,05),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.4],[new Date(2012,4,05,13,57,05),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.4],[new Date(2012,4,05,14,12,05),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.4],[new Date(2012,4,05,14,27,05),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.4],[new Date(2012,4,05,14,42,05),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.4],[new Date(2012,4,05,14,57,05),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.6],[new Date(2012,4,05,15,12,06),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.6],[new Date(2012,4,05,15,27,06),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.6],[new Date(2012,4,05,15,42,06),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,15,57,06),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.6],[new Date(2012,4,05,16,12,09),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.6],[new Date(2012,4,05,16,27,09),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.6],[new Date(2012,4,05,16,42,09),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.6],[new Date(2012,4,05,16,57,10),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,17,12,10),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,17,27,10),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,17,42,10),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,17,57,10),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,18,12,10),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,18,27,10),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,18,42,11),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,18,57,11),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,19,12,11),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,19,27,11),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,19,42,11),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,19,57,11),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,20,12,11),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.9],[new Date(2012,4,05,20,27,11),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.9],[new Date(2012,4,05,20,42,11),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.9],[new Date(2012,4,05,20,57,12),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,21,12,12),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.9],[new Date(2012,4,05,21,27,12),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.9],[new Date(2012,4,05,21,42,12),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,21,57,12),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,22,12,12),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,22,27,13),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,22,42,13),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,22,57,13),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,23,12,13),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,23,27,13),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,23,42,13),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.6,22.6],[new Date(2012,4,05,23,57,13),-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,-17.8,25.4,22.6]]
//         series:[{name: ['Curve 1','Curve 2'],data: [[1,2,3],[3,4,5],[5,6,7],[7,8,9],[9,0,1]]}]
?>
<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.7.1/jquery.min.js" type="text/javascript"></script>
<script src="http://code.highcharts.com/stock/highstock.js" type="text/javascript"></script>
  <script type="text/javascript">
var chart; // globally available
$(document).ready(function() {
      chart = new Highcharts.StockChart({
         chart: {
            renderTo: 'container'
         },
        xAxis: {
            type: 'datetime'
        },
        yAxis: {

        },
		rangeSelector: {
			buttons: [{type: 'day',count: 1,text: '1d'},
						{type: 'month',count: 1,text: '1m'},
						{type: 'month',count: 3,text: '3m'},
						{type: 'month',count: 6,text: '6m'},
						{type: 'ytd',text: 'YTD'},
						{type: 'year',count: 1,text: '1y'},
						{type: 'all',text: 'All'}]
		},
		series: [
			{name: 'Marine', data:[]},{name: 'M&M', data:[]},{name: 'Amis', data:[]},{name: 'Dressing', data:[]},{name: 'SdB', data:[]},
			{name: 'Bureau', data:[]},{name: 'Salon', data:[]},{name: 'Cuisine', data:[]},{name: 'Couloir', data:[]},{name: 'Terrasse', data:[]},
			{name: 'UPS', data:[]},{name: 'Rack', data:[]}
		]
      });
<?php
  define("NOM","lebomb");         //monnom = login chez free
  define("PASSE","genesis");     // monpasse=votre mot de passe free
  define("SERVEUR","sql.free.fr");// adresse du serveur free
  define("BASE","lebomb");       //nombase = login chez free

  //--Connexion au serveur
  $link = mysql_connect(SERVEUR,NOM,PASSE);

  if(!$link) {echo "Impossible de se connecter au serveur".mysql_error();exit;}
  //--Connexion ? la base
  mysql_select_db(BASE,$link);

  $requete= "SELECT * FROM lb WHERE `DATE` BETWEEN '2012-01-01 00:00:00' AND '2012-12-31 23:59:59' ORDER BY DATE";
  $result=mysql_query($requete, $link) or die("Echec de lecture".mysql_error());

  $first = 1;
  while($r=mysql_fetch_array($result, MYSQL_ASSOC))
    //{echo "DATE: $r[DATE] TEMP0: $r[TEMP0] TEMP1: $r[TEMP1] TEMP2: $r[TEMP2] TEMP3: $r[TEMP3]<br>";}
    {
      //if($first==1) {$first=0;} else {echo ",";}
      $fullDate = $r[DATE];
      $temp = substr($fullDate, 0, 4).","; // Annee
      $temp .= ((string)(((int)substr($fullDate, 5, 2))-1)).","; // Mois
      $temp .= substr($fullDate, 8, 2).","; // Jour
      $temp .= substr($fullDate, 11, 2).","; // Heure
      $temp .= substr($fullDate, 14, 2).","; // Minute
      $temp .= substr($fullDate, 17, 2); // Second

      for($i=0; $i<10; $i++)
      {
		echo "chart.series[".$i."].addPoint([Date.UTC(".$temp."),".$r['room'.sprintf('%02d',$i).'_temp_value']."],false);\n";
      	//echo $r['room'.sprintf('%02d',$i).'_temp_value'].",";
      }
	  echo "chart.series[".$i."].addPoint([Date.UTC(".$temp."),".$r['safety_ups_temp']."],false);\n";
      //echo $r['safety_ups_temp'].",";
	  $i = $i + 1;
	  echo "chart.series[".$i."].addPoint([Date.UTC(".$temp."),".$r['safety_rack_temp']."],false);\n";
      //echo $r['safety_rack_temp']."]";
    }
	echo "chart.redraw();\n";
?>
   });
   </script>
</head>
<body style="font-family: Arial;border: 0 none;">
<div id="container" style="width: 100%; height: 400px"></div>
</body>
</html>
