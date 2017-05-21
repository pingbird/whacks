import 'package:flutter/material.dart';
import 'dart:async';
import 'dart:convert';
import 'dart:io';

void main() {
  runApp(new MyApp());
}

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return new MaterialApp(
      title: 'Whacks',
      theme: new ThemeData(
        primarySwatch: Colors.green,
      ),
      home: new MyHomePage(title: 'WHacks'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  MyHomePage({Key key, this.title}) : super(key: key);
  final String title;
  @override
  _MyHomePageState createState() => new _MyHomePageState();
}

class Entry {
  Entry(this.name, this.time, this.distance);
  String name;
  int time;
  int distance;
}

class _MyHomePageState extends State<MyHomePage> {
  List<Entry> entries = [];

  void _update(Timer t) {
    if (t != null && !mounted) {
      t.cancel();
      return;
    }
    new HttpClient().getUrl(Uri.parse("http://enp.pxtst.com/app.php")).then((req) {
      return req.close();
    }).then((resp) async {
      var str = (await resp.transform(UTF8.decoder).toList()).join();
      setState(() {
        entries = (JSON.decode(str) as List<List>).map((o) {
          return new Entry(o[0], int.parse(o[1]), int.parse(o[2]));
        }).toList();
      });
    });
  }

  @override
  void initState() {
    super.initState();
    _update(null);
    new Timer.periodic(new Duration(seconds: 5), (t) => _update(t));
  }

  @override
  Widget build(BuildContext context) {
    return new Scaffold(
      appBar: new AppBar(
        title: new Text(widget.title),
      ),
      body: new ListView(children: entries.map((e) => new Column(children: [
        new Container(padding: new EdgeInsets.all(8.0), child: new Row(mainAxisAlignment: MainAxisAlignment.start, children: [
          new Column(crossAxisAlignment: CrossAxisAlignment.start, children: [
            new Text(e.name, style: new TextStyle(fontSize: 30.0)),
            new Text(new DateTime.fromMillisecondsSinceEpoch(e.time * 1000).toLocal().toString()),
          ]),
          new Expanded(child: new Column(crossAxisAlignment: CrossAxisAlignment.end, children: [
            new Text(e.distance.toString() + " cm", style: new TextStyle(fontSize: 20.0)),
          ])),
        ])),
        new Divider(),
      ])).toList()),
    );
  }
}
