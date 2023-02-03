# Code Review of Pattern

[toc]

## expr(Node end)方法
正则规则处理流程

```mermaid
sequenceDiagram

loop 循环处理

    expr->>sequence: 交替之间的序列分析

    alt is '('
        sequence->>group0: 捕获组
    else is '['
        sequence->>clazz: Character classes 字符组
    else is '\\'
        alt is 'P'
            sequence->>family: family
        else is others
            sequence->>atom: atom
        end
    end

end


```

```java
String REGEX_TEL = "^(\\d{3,4}-)?\\d{6,8}$";
Pattern PATTERN_REGEX_TEL = Pattern.compile(REGEX_TEL);
```

```mermaid
graph TB

matchRoot:$Begin#37-->next:$Branch#55

next:$Branch#55-->atoms:$Node*2*#60
next:$Branch#55-->|member:conn|$BranchConn#61
next:$Branch#55-->accept((next:$Node#50))
next:$Branch#55-->size:2

atoms:$Node*2*#60-->0:$GroupHead#40
atoms:$Node*2*#60-->1:null

0:$GroupHead#40-->localIndex#1(localIndex:0)
0:$GroupHead#40-->next:$Curly#47

next:$Curly#47-->atom:$Ctype#45
next:$Curly#47-->cmax:4
next:$Curly#47-->cmin:3
next:$Curly#47-->next:$Single#49
next:$Curly#47-->type#1(type:0)

atom:$Ctype#45-->ctype:1024
atom:$Ctype#45-->accept((next:$Node#50))

next:$Single#49-->c:45
next:$Single#49-->next:$GroupTail#41
next:$Single#49-->type#2(type:0)

next:$GroupTail#41-->groupIndex:2
next:$GroupTail#41-->localIndex#2(localIndex:0)
next:$GroupTail#41-->|member:next|$BranchConn#61


$BranchConn#61-->next:$Curly#57


next:$Curly#57-->atom:$Ctype#56
next:$Curly#57-->cmax:8
next:$Curly#57-->cmin:6
next:$Curly#57-->next:$Dollar#59
next:$Curly#57-->type#3(type:0)

atom:$Ctype#56-->ctype:1024
atom:$Ctype#56-->accept((next:$Node#50))

next:$Dollar#59-->multiline:false
next:$Dollar#59-->lastAccept([next:LastNode#35])

lastAccept-->accept((next:$Node#50))

```
上述`Node`结构说明如下：
- 统一使用`#`代替`@`，`@`为mermaid制图工具的特殊符号
- `$Node*2*`即为`$Node[2]`,[]在mermaid制图工具为直角长方形
- next:$Node#50为类`Pattern`的静态成员`accept`
- next:LastNode#35为类`Pattern`的静态成员`lastAccept`
- next:$Curly#47的说明：
  - ctype:1024，类型定义在类`ASCII`中`static final int DIGIT   = 0x00000400;`，表明是数字类型，
  - 长度为cmax=4，cmin=3
  - 匹配正则表达式中的`d{3,4}`要求
