def Enter(uid,nick_enter,users,msg_list):
    if type(msg_list)==int: # type integer : check  / type list : print
        if uid not in users:
            users[uid]=[nick_enter,"on"] 
        if uid in users and users[uid][1]=="off":
            users[uid][1]="on"
            Change(uid,nick_enter,users,msg_list)
    else :  
        nick = users[uid][0]
        msg = nick+"님이 들어왔습니다."
        msg_list.append(msg)

def Leave(uid,nick_notUse,users,msg_list):
    if type(msg_list)==int: # type integer : check  / type list : print
        users[uid][1]="off"
    else :
        nick = users[uid][0]
        msg = nick+"님이 나갔습니다."
        msg_list.append(msg)
    

def Change(uid,nick,users,msg_list):
    if type(msg_list)==int: # type integer : check  / type list : print
        users[uid][0]=nick

def solution(record):
    answer = []
    cmdDict={
        "Enter":Enter,
        "Leave":Leave,
        "Change":Change
    }
    
    cmd_list=[]
    for cmd in record:
        t = list(cmd.split(" "))
        cmd_list.append(t)
    
    users={}
    
    #final nickname simulation
    for cmd in cmd_list:
        param1=cmd[0]#cmd
        param2=cmd[1]#uid
        param3=""#nickname
        if len(cmd)==3 :
            param3=cmd[2]
        param4=users
        cmdDict[param1](param2,param3,param4,1)
    
    #print msg
    for cmd in cmd_list:
        param1=cmd[0]#cmd
        if param1 == "Change":
            continue
        param2=cmd[1]#uid
        param3=""#nickname
        if len(cmd)==3 :
            param3=cmd[2]
        param4=users
        cmdDict[param1](param2,param3,param4,answer)

    return answer


"""
#note

GOAL : 모든 기록 처리 후 최종적으로 방 개설한 사람이 보게되는 메세지 문자열

#in : "[닉네임]님이 들어왔습니다." : Enter uid nickname
#out : "[닉네임]님이 나갔습니다." : Leave uid nickname
#닉네임변경 : 중복가능 : change uid nickname

"""
