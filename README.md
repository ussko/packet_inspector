## Пример выполнения тестового задания: разбор сетевых данных

### Дано:
Файл с пакетами трафика, захваченного с сетевой карты (стек протоколов вымышленный). Описание сетевой модели и протоколов представлено ниже.

### Требуется:
Создать программу на C++, собирающую по данному файлу следующую статистику:
1. Количество пакетов NETWORK V1
2. Количество пакетов NETWORK V2
3. Количество уникальных адресов устройств NETWORK V1
4. Количество уникальных адресов устройств NETWORK V2
5. Количество пакетов TRANSPORT V1
6. Количество пакетов TRANSPORT V2
7. Количество пакетов TRANSPORT V1 с ошибочной контрольной суммой
8. Количество пакетов TRANSPORT V2 с ошибочной контрольной суммой
9. Количество уникальных портов TRANSPORT V1
10. Количество уникальных портов TRANSPORT V2
11. Количество сессий TRANSPORT V2
12. Количество пакетов TEXT
13. Количество пакетов JSON
14. Количество пакетов BINARY

### Сетевая модель
|#|Уровень|Протокол|
|-|-------|--------|
|3|Application|TEXT, JSON, BINARY|
|2|Transport|TRANSPORT V1, TRANSPORT V2|
|1|Network|NETWORK V1, NETWORK V2|

### Иерархия протоколов
<table>
  <tbody>
    <tr>
      <td colspan=3></td>
      <td>Application Data</td>
      <td></td>
    </tr>
    <tr>
      <td colspan=2></td>
      <td>Transport Header</td>
      <td>Transport Data</td>
      <td>Checksum</td>
    </tr>
    <tr>
      <td>Network Header</td>
      <td>Checksum</td>
      <td colspan=3>Network Data</td>
    </tr>
  </tbody>
</table>

### Порядок байт
Порядок байт в пакетах big-endian.
Например, рассмотрим число 123456789 в десятичной системе счисления.
Это же число в двоичной системе счисления: 00000111 01011011 11001101 00010101.
Будет записано в пакете так:
|Порядок байт в пакете|Значение|
|---------------------|--------|
|1|00000111|
|2|01011011|
|3|11001101|
|4|00010101|

### Сетевой уровень
#### NETWORK V1
<table>
  <thead>
    <tr>
      <th>Байт</th>
      <th></th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>0</td>
      <td align="center">Version (0x01)</td>
    </tr>
    <tr>
      <td>1</td>
      <td rowspan=4 align="center">Source Address</td>
    </tr>
    <tr>
      <td>2</td>
    </tr>
    <tr>
      <td>3</td>
    </tr>
    <tr>
      <td>4</td>
    </tr>
    <tr>
      <td>5</td>
      <td rowspan=4 align="center">Destination Address</td>
    </tr>
    <tr>
      <td>6</td>
    </tr>
    <tr>
      <td>7</td>
    </tr>
    <tr>
      <td>8</td>
    </tr>
    <tr>
      <td>9</td>
      <td align="center">Protocol</td>
    </tr>
    <tr>
      <td>10</td>
      <td rowspan=2 align="center">Data Size</td>
    </tr>
    <tr>
      <td>11</td>
    </tr>
    <tr>
      <td>12</td>
      <td rowspan=2 align="center">Header Checksum</td>
    </tr>
    <tr>
      <td>13</td>
    </tr>
    <tr>
      <td>14 - N</td>
      <td align="center">Data</td>
    </tr>
  </tbody>
</table>

#### NETWORK V2
<table>
  <thead>
    <tr>
      <th>Байт</th>
      <th></th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>0</td>
      <td align="center">Version (0x02)</td>
    </tr>
    <tr>
      <td>1</td>
      <td rowspan=6 align="center">Source Address</td>
    </tr>
    <tr>
      <td>2</td>
    </tr>
    <tr>
      <td>3</td>
    </tr>
    <tr>
      <td>4</td>
    </tr>
    <tr>
      <td>5</td>
    </tr>
    <tr>
      <td>6</td>
    </tr>
    <tr>
      <td>7</td>
      <td rowspan=6 align="center">Destination Address</td>
    </tr>
    <tr>
      <td>8</td>
    </tr>
    <tr>
      <td>9</td>
    </tr>
    <tr>
      <td>10</td>
    </tr>
    <tr>
      <td>11</td>
    </tr>
    <tr>
      <td>12</td>
    </tr>
    <tr>
      <td>13</td>
      <td align="center">Protocol</td>
    </tr>
    <tr>
      <td>14</td>
      <td rowspan=2 align="center">Data Size</td>
    </tr>
    <tr>
      <td>15</td>
    </tr>
    <tr>
      <td>16</td>
      <td rowspan=2 align="center">Header Checksum</td>
    </tr>
    <tr>
      <td>17</td>
    </tr>
    <tr>
      <td>18 - N</td>
      <td align="center">Data</td>
    </tr>
  </tbody>
</table>

Для протоколов NETWORK V1 и NETWORK V2 гарантируется отсутствие ошибок в заголовках и, соответственно, не может быть пакетов с ошибочным значением контрольной суммы Header Checksum.

**Описание полей протоколов сетевого уровня**
|Поле|Описание|
|----|--------|
|Version|Версия протокола|
|Source Address|Адрес отправителя|
|Destination Address|Адрес получателя|
|Protocol|Протокол верхнего уровня. Пакет протокола верхнего уровня помещается в поле Data.<br>Значения поля:<br>  1. 0x01 - TRANSPORT V1<br>  2. 0x02 - TRANSPORT V2|
|Data Size|Размер полезных данных|
|Header Checksum|Контрольная сумма для проверки целостности заголовка. Сумма всех байт заголовка по модулю 2^16|
|Data|Полезные данные|

### Транспортный уровень
#### TRANSPORT V1
<table>
  <thead>
    <tr>
      <th>Байт</th>
      <th></th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>0</td>
      <td rowspan=2 align="center">Source Port</td>
    </tr>
    <tr>
      <td>1</td>
    </tr>
    <tr>
      <td>2</td>
      <td rowspan=2 align="center">Destination Port</td>
    </tr>
    <tr>
      <td>3</td>
    </tr>
    <tr>
      <td>4</td>
      <td rowspan=2 align="center">Data Size</td>
    </tr>
    <tr>
      <td>5</td>
    </tr>
    <tr>
      <td>6 - N</td>
      <td align="center">Data</td>
    </tr>
    <tr>
      <td>N+1</td>
      <td rowspan=2 align="center">Checksum</td>
    </tr>
    <tr>
      <td>N+2</td>
    </tr>
  </tbody>
</table>

#### TRANSPORT V2
<table>
  <thead>
    <tr>
      <th>Байт</th>
      <th></th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>0</td>
      <td rowspan=2 align="center">Source Port</td>
    </tr>
    <tr>
      <td>1</td>
    </tr>
    <tr>
      <td>2</td>
      <td rowspan=2 align="center">Destination Port</td>
    </tr>
    <tr>
      <td>3</td>
    </tr>
    <tr>
      <td>4</td>
      <td rowspan=4 align="center">Fragment Number</td>
    </tr>
    <tr>
      <td>5</td>
    </tr>
    <tr>
      <td>6</td>
    </tr>
    <tr>
      <td>7</td>
    </tr>
    <tr>
      <td>8</td>
      <td align="center">F (0x01), L (0x02)</td>
    </tr>
    <tr>
      <td>9</td>
      <td rowspan=2 align="center">Data Size</td>
    </tr>
    <tr>
      <td>10</td>
    </tr>
    <tr>
      <td>11 - N</td>
      <td align="center">Data</td>
    </tr>
    <tr>
      <td>N+1</td>
      <td rowspan=2 align="center">Checksum</td>
    </tr>
    <tr>
      <td>N+2</td>
    </tr>
  </tbody>
</table>

**Сессией протокола TRANSPORT V2** называется набор пакетов с последовательными порядковыми номерами фрагментов Fragment Number (включая пакеты с флагами F и L), переданных от одной конечной точки (конкретные Source Address и Source Port) до другой (конкретные Destination Address и Destination Port). В файле входных данных пакеты, относящиеся к одной сессии, могут лежать не по порядку, могут быть разделены пакетами других сессий. А также пакеты с некоторыми порядковыми номерами фрагментов вообще могут отсутствовать, в таком случае сессия не может быть собрана.

**Описание полей протоколов транспортного уровня**
|Поле|Описание|
|----|--------|
|Source Port|Порт отправителя|
|Destination Port|Порт получателя|
|Fragment Number|Порядковый номер фрагмента [0, 2^32]|
|F|Первый пакет в сессии|
|L|Последний пакет в сессии|
|Data Size|Размер полезных данных|
|Data|Полезные данные|
|Checksum|Контрольная сумма для проверки целостности пакета. Сумма всех байт пакета транспортного уровня по модулю 2^16|

### Прикладной уровень
TEXT - текст в формате ASCII
JSON - текстовые данные в формате JSON
BINARY - неструктурированные бинарные данные
