import sys
from datetime import datetime
from datetime import timedelta


class Msg:
    def __init__(self, msg, level):
        self.msg = msg
        self.level = level


def epochTimeToString(epochTime):
    epochTime = int(epochTime)
    epochTime /= 1000
    return datetime.fromtimestamp(epochTime)


if len(sys.argv) < 9:
    exit(11)
elif (len(sys.argv) - 6) % 2 != 1:
    exit(12)
fileName = sys.argv[1]
numOfMsg = sys.argv[2]
pid = sys.argv[3]
tid = sys.argv[4]
startTime = sys.argv[5]
loggerName = sys.argv[6]
curTime = epochTimeToString(startTime)
loggerNameStart = 0
loggerNameEnd = len(loggerName) + loggerNameStart
levelStart = loggerNameEnd
timeIsStr = " - time is: "
pidIs = ". process id is: "
messagePre = ". message is: "
DATE_FORMAT = "%d.%m.%Y|%H:%M:%S|%f"
dateLen = len(curTime.strftime(DATE_FORMAT)) - 3
timeDelta = timedelta(seconds=2)


def checkLine(line, msg):
    global curTime
    global timeDelta
    if line[loggerNameStart:loggerNameEnd] != loggerName:
        return False
    levelStr = "(" + msg.level + ")"
    levelEnd = levelStart + len(levelStr)
    if line[levelStart:levelEnd] != levelStr:
        return False
    timeIsStrStart = levelEnd
    timeIsStrEnd = timeIsStrStart + len(timeIsStr)
    if line[timeIsStrStart:timeIsStrEnd] != timeIsStr:
        return False
    timeStart = timeIsStrEnd
    timeEnd = timeStart + dateLen
    try:
        lineTime = datetime.strptime(line[timeStart:timeEnd], DATE_FORMAT)
    except ValueError:
        return False
    delta = lineTime - curTime
    if delta < timedelta():
        delta = -delta
    curTime = lineTime
    if delta > timeDelta:
        return False
    timeDelta = timedelta(milliseconds=500)
    pidIsIndex = line.index(pidIs)
    pidStart = pidIsIndex + len(pidIs)
    pidEnd = pidStart + len(pid)
    if line[pidStart:pidEnd] != pid:
        return False
    messagePreStart = pidEnd
    messagePreEnd = messagePreStart + len(messagePre)
    if line[messagePreStart:messagePreEnd] != messagePre:
        return False
    msgStart = messagePreEnd
    msgEnd = msgStart + len(msg.msg)
    if line[msgStart:msgEnd] != msg.msg:
        return False
    tIdStart = msgEnd + 4
    tIdEnd = tIdStart + len(tid)
    if line[tIdStart:tIdEnd] != tid:
        return False
    return True


msgs = []
for i in range(7, len(sys.argv), 2):
    msgs.append(Msg(sys.argv[i + 1], sys.argv[i]))
with open(fileName, "r") as file:
    fileLines = file.readlines()
isError = False
if len(fileLines) != int(numOfMsg):
    exit(2)
for i in range(len(fileLines)):
    if not checkLine(fileLines[i], msgs[i % len(msgs)]):
        isError = True
        print("ERROR:line number{0}. line is:{1}".format(i, fileLines[i].strip()))
if isError:
    exit(1)
exit(0)
