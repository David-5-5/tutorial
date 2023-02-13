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

## 分析一个简单的例子
```java
String REGEX_TEL = "^(\\d{3,4}-)?\\d{6,8}$";
Pattern PATTERN_REGEX_TEL = Pattern.compile(REGEX_TEL);
```

### 返回值

返回值matchRoot及其结构如下：

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
- 基本说明：
  - 统一使用`#`代替`@`，`@`为mermaid制图工具的特殊符号
  - `$Node*2*`即为`$Node[2]`,[]在mermaid制图工具为直角长方形
  - $Node#50为类`Pattern`的静态成员`accept`, 并为多个Node节点共享
  - LastNode#35为类`Pattern`的静态成员`lastAccept`
- 起始类型节点`matchRoot:$Begin#37`, `Begin`类型节点对应于正则串中起始字符`^`,而`Dollar`类型节点对应于正则串中起始字符`$`
- 接下来就是`next:$Branch#55`，表明正则表达式包含多个分支，可以通过如下示例，进一步了解正则表达式是否包含分支：
  - `^d{6,8}$` **不包含** ~~`Branch`~~ 节点
  - `d{6,8}` **不包含** ~~`Branch`~~ 节点
  - `(\\d{6,8})?` **包含**`Branch`节点。*注*，若为`(...)+`格式，则**包含**`Prolog`节点
  - `Branch`节点包含`atoms`为`Node`节点数组。
- `0:$GroupHead#40`为`Branch.atoms[0]`,当遇到'(',捕获group
- Group节点，即()中包含`next:$Curly#47`的说明：
  - Curly对应正则表达式中{...}格式规则
  - `atom$Ctype#45`节点，ctype:1024，类型定义在类`ASCII`中`static final int DIGIT = 0x00000400;`，表明是数字类型，同时Ctpye节点包括如下字符类型：
    - 数字及非数字类型, 类型定义为`ASCII.DIGIT`, 正则表达式中写法为：`\d`, `\D`
    - 字符及非字符类型, 类型定义为`ASCII.WORD`, 正则表达式中写法为：`\w`, `\W`
    - 空格及非空格类型, 类型定义为`ASCII.SPACE`, 正则表达式中写法为：`\s`, `\S`
    - `atom`变量，`atom()`解析一个Slice类型或Single类型节点
  - 长度为cmax=4，cmin=3
  - 以上匹配正则表达式中的`\\d{3,4}`要求
  - 子节点`next:$Single#49`，对应于正则串中起始字符`-`。Single类型节点代表一个独立的字符。如果多个字符，例如`--`，将使用Slice类型节点
