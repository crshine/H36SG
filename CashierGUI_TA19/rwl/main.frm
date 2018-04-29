VERSION 5.00
Begin VB.Form frmMain 
   Caption         =   "RWL Sample (v3.9)"
   ClientHeight    =   6885
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9045
   Icon            =   "main.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   6885
   ScaleWidth      =   9045
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdFirmware 
      BackColor       =   &H00FFFF80&
      Caption         =   "Fir&mware"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   500
      Left            =   6120
      MaskColor       =   &H0000FFFF&
      Style           =   1  'Graphical
      TabIndex        =   37
      Top             =   3840
      UseMaskColor    =   -1  'True
      Width           =   1300
   End
   Begin VB.Frame fmDD 
      Caption         =   "Defer Deduct"
      Height          =   855
      Left            =   1560
      TabIndex        =   33
      Top             =   3240
      Width           =   3735
      Begin VB.CommandButton cmdDeferDeduct 
         Caption         =   "INIT &1"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Index           =   1
         Left            =   120
         TabIndex        =   34
         Top             =   240
         Width           =   1000
      End
      Begin VB.CommandButton cmdDeferDeduct 
         Caption         =   "FINAL &3"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Index           =   3
         Left            =   2520
         TabIndex        =   36
         Top             =   240
         Width           =   1000
      End
      Begin VB.CommandButton cmdDeferDeduct 
         Caption         =   "CONT &2"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Index           =   2
         Left            =   1320
         TabIndex        =   35
         Top             =   240
         Width           =   1000
      End
   End
   Begin VB.CommandButton CmdHouse 
      BackColor       =   &H00FFFF80&
      Caption         =   "&House"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   500
      Left            =   7440
      MaskColor       =   &H0000FFFF&
      Style           =   1  'Graphical
      TabIndex        =   32
      Top             =   3840
      UseMaskColor    =   -1  'True
      Width           =   1300
   End
   Begin VB.CommandButton cmdPortClose 
      BackColor       =   &H00FFFF80&
      Caption         =   "Por&tClose"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   500
      Left            =   6120
      MaskColor       =   &H0000FFFF&
      Style           =   1  'Graphical
      TabIndex        =   31
      Top             =   2640
      UseMaskColor    =   -1  'True
      Width           =   1300
   End
   Begin VB.CommandButton cmdInit 
      BackColor       =   &H00FFFF80&
      Caption         =   "&InitComm"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   500
      Left            =   7440
      MaskColor       =   &H0000FFFF&
      Style           =   1  'Graphical
      TabIndex        =   30
      Top             =   2640
      UseMaskColor    =   -1  'True
      Width           =   1300
   End
   Begin VB.CommandButton cmdWriteID 
      BackColor       =   &H00FFFF80&
      Caption         =   "&WriteID"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   500
      Left            =   6120
      MaskColor       =   &H00000000&
      Style           =   1  'Graphical
      TabIndex        =   29
      Top             =   2040
      UseMaskColor    =   -1  'True
      Width           =   1300
   End
   Begin VB.CommandButton cmdTimeVer 
      BackColor       =   &H00FFFF80&
      Caption         =   "Time&Ver"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   500
      Left            =   7440
      MaskColor       =   &H0000FFFF&
      Style           =   1  'Graphical
      TabIndex        =   28
      Top             =   3240
      UseMaskColor    =   -1  'True
      Width           =   1300
   End
   Begin VB.TextBox txtCurDir 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   7200
      TabIndex        =   26
      Text            =   "c:\rwl"
      Top             =   960
      Width           =   1695
   End
   Begin VB.CommandButton cmdReset 
      BackColor       =   &H00FFFF80&
      Caption         =   "Re&set"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   500
      Left            =   6120
      MaskColor       =   &H0000FFFF&
      Style           =   1  'Graphical
      TabIndex        =   8
      Top             =   3240
      UseMaskColor    =   -1  'True
      Width           =   1300
   End
   Begin VB.CommandButton cmdAdd 
      Caption         =   "&Add"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   500
      Left            =   2760
      TabIndex        =   5
      Top             =   2640
      Width           =   1300
   End
   Begin VB.CommandButton cmdPIN 
      Caption         =   "PI&N"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   500
      Left            =   4080
      TabIndex        =   6
      Top             =   2640
      Width           =   1300
   End
   Begin VB.TextBox txtFileName 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   7200
      TabIndex        =   1
      Top             =   1440
      Width           =   1695
   End
   Begin VB.CommandButton cmdFare 
      Caption         =   "&Fare"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   500
      Left            =   120
      TabIndex        =   7
      Top             =   3600
      Width           =   1300
   End
   Begin VB.TextBox txtTimeout 
      Height          =   375
      Left            =   1800
      TabIndex        =   23
      Text            =   "10"
      Top             =   2160
      Width           =   1575
   End
   Begin VB.CommandButton cmdLog 
      Caption         =   "&Log"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   500
      Left            =   120
      TabIndex        =   0
      Top             =   3120
      Width           =   1300
   End
   Begin VB.TextBox txtAddInfo 
      Height          =   375
      Left            =   1680
      TabIndex        =   11
      Text            =   "0102"
      Top             =   600
      Width           =   2055
   End
   Begin VB.TextBox txtBlockInfo 
      Height          =   375
      Left            =   1680
      TabIndex        =   12
      Text            =   "A1A2A3A4A5"
      Top             =   1080
      Width           =   2055
   End
   Begin VB.TextBox txtResult 
      Height          =   375
      Left            =   1800
      TabIndex        =   15
      TabStop         =   0   'False
      Top             =   1680
      Width           =   1575
   End
   Begin VB.TextBox txtDump 
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2535
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   13
      TabStop         =   0   'False
      Top             =   4320
      Width           =   5415
   End
   Begin VB.CommandButton cmdXFile 
      BackColor       =   &H00FFFF80&
      Caption         =   "&XFile"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   500
      Left            =   7440
      MaskColor       =   &H0000FFFF&
      Style           =   1  'Graphical
      TabIndex        =   9
      Top             =   2040
      UseMaskColor    =   -1  'True
      Width           =   1300
   End
   Begin VB.CommandButton cmdPoll 
      Caption         =   "&Poll"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   500
      Left            =   120
      TabIndex        =   3
      Top             =   2640
      Width           =   1300
   End
   Begin VB.TextBox txtSource 
      Height          =   375
      Left            =   1680
      TabIndex        =   10
      Text            =   "1"
      Top             =   120
      Width           =   1575
   End
   Begin VB.CommandButton cmdDeduct 
      Caption         =   "&Deduct"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   500
      Left            =   1440
      TabIndex        =   4
      Top             =   2640
      Width           =   1300
   End
   Begin VB.Label C 
      Caption         =   "Cur Dir."
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   6000
      TabIndex        =   27
      Top             =   960
      Width           =   1455
   End
   Begin VB.Image Image1 
      Height          =   660
      Left            =   6960
      Picture         =   "main.frx":0EC2
      Top             =   120
      Width           =   1920
   End
   Begin VB.Line Line2 
      X1              =   5760
      X2              =   5760
      Y1              =   360
      Y2              =   6360
   End
   Begin VB.Label Label8 
      Caption         =   "File name"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   6000
      TabIndex        =   2
      Top             =   1440
      Width           =   1455
   End
   Begin VB.Label Label7 
      Caption         =   "Poll Timeout"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   240
      TabIndex        =   25
      Top             =   2160
      Width           =   1695
   End
   Begin VB.Label Label6 
      Caption         =   "(0.1 sec)"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Index           =   3
      Left            =   3480
      TabIndex        =   24
      Top             =   2160
      Width           =   1335
   End
   Begin VB.Label Label6 
      Caption         =   "(5 hex)"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Index           =   2
      Left            =   3840
      TabIndex        =   22
      Top             =   1080
      Width           =   975
   End
   Begin VB.Label Label6 
      Caption         =   "(2 hex)"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Index           =   1
      Left            =   3840
      TabIndex        =   21
      Top             =   600
      Width           =   975
   End
   Begin VB.Label Label6 
      Caption         =   "(10 cents)"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Index           =   0
      Left            =   3600
      TabIndex        =   20
      Top             =   120
      Width           =   1335
   End
   Begin VB.Label Label5 
      Caption         =   "(10 cents)"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3480
      TabIndex        =   19
      Top             =   1680
      Width           =   1335
   End
   Begin VB.Line Line1 
      X1              =   240
      X2              =   4920
      Y1              =   1560
      Y2              =   1560
   End
   Begin VB.Label Label4 
      Caption         =   "Block Info"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   360
      TabIndex        =   18
      Top             =   1080
      Width           =   1455
   End
   Begin VB.Label Label3 
      Caption         =   "Add. Info"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   360
      TabIndex        =   17
      Top             =   600
      Width           =   1455
   End
   Begin VB.Label Label2 
      Caption         =   "Remain Value "
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   240
      TabIndex        =   16
      Top             =   1680
      Width           =   1935
   End
   Begin VB.Label Label1 
      Caption         =   "Amount"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   360
      TabIndex        =   14
      Top             =   120
      Width           =   1095
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' Struct for Version
Private Type DevVerRec
    DevID As Long
    OperID As Long
    DevTime As Long
    CompID As Long
    KeyVer As Long
    EODVer As Long
    BLVer As Long
    FIRMVer As Long
    CCHSVer As Long
    CSSer As Long
    Reserved1 As Long
    Reserved2 As Long
End Type

Private Declare Function FirmUpg Lib "rwl" Alias "_FirmUpg@4" (ByVal filename As String) As Long
Private Declare Function InitComm Lib "rwl" Alias "_InitComm@8" (ByVal Port As Byte, ByVal Baud As Long) As Long
Private Declare Function Deduct Lib "rwl" Alias "_Deduct@8" (ByVal i As Long, AI As Any) As Long
Private Declare Function DeferDeduct Lib "rwl" Alias "_DeferDeduct@12" (ByVal State As Byte, ByVal i As Long, AI As Any) As Long
Private Declare Function AddValue Lib "rwl" Alias "_AddValue@12" (ByVal v As Long, ByVal avtype As Byte, AI As Any) As Long
Private Declare Function SendBlack Lib "rwl" Alias "_SendBlack@4" (ByVal filename As String) As Long
Private Declare Function Reset Lib "rwl" Alias "_Reset@0" () As Long
Private Declare Function TxnAmt Lib "rwl" Alias "_TxnAmt@16" (ByVal Amt As Long, ByVal RV As Long, ByVal Sound As Byte, ByVal LED As Byte) As Long
Private Declare Function Poll Lib "rwl" Alias "_Poll@12" (ByVal Com As Byte, ByVal Timeout As Byte, ByVal PollData As String) As Long
Private Declare Function PortClose Lib "rwl" Alias "_PortClose@0" () As Long
Private Declare Function PIN Lib "rwl" Alias "_PIN@8" (ByVal oldpin As Long, ByVal newpin As Long) As Long
Private Declare Function TimeVer Lib "rwl" Alias "_TimeVer@4" (ByRef Ver As DevVerRec) As Long
Private Declare Function WriteID Lib "rwl" Alias "_WriteID@4" (ByVal id As Long) As Long
Private Declare Function XFile Lib "rwl" Alias "_XFile@4" (ByVal XFileName As String) As Long
Private Declare Function HouseKeeping Lib "rwl" Alias "_HouseKeeping@0" () As Long



Public Sub HexDump(ByRef p() As Byte, ByVal l As Integer)
' Dump the byte array in hex
    For i = 0 To l - 1
        If p(i) < 16 Then
            txtDump.Text = txtDump.Text & "0"
        End If
        txtDump.Text = txtDump.Text & Hex(p(i)) & " "
        If i Mod 16 = 15 Then
            txtDump.Text = txtDump.Text & vbCrLf
        End If
    Next i
End Sub


Public Function cvDate(d As Long) As String
    Dim f As Double
    Dim R As String
' Convert the card log date/time to human readable format

    f = 36526 + CDbl(d) / 86400 + 1 / 3 ' VB use 30/12/1899 0:0:0 as base
    R = Format(Day(f), "00") & "/" & Format(Month(f), "00") & "/" & Year(f) & "   "
    R = R & Format(Hour(f), "00") & ":" & Format(Minute(f), "00") & ":" & Format(Second(f), "00")
    
    cvDate = R
End Function

Private Function toDec(v As String) As Byte
    Dim h, l As Byte
    Dim R As Byte
        
'Convert a two character hex string to decimal
    h = Asc(Mid(v, 1, 1))
    l = Asc(Mid(v, 2, 1))
    R = IIf(h >= Asc("A"), h - Asc("A") + 10, h - Asc("0"))
    R = R * 16 + IIf(l >= Asc("A"), l - Asc("A") + 10, l - Asc("0"))
    
    toDec = R
End Function


Private Sub cmdAdd_Click()
Dim UD(32) As Byte

    txtResult = "Adding..."
    DoEvents
    UD(0) = 0
    For i = 0 To 4 'the additional info
        UD(i + 1) = toDec(Mid(txtBlockInfo, i * 2 + 1, 2))
    Next i
    R = AddValue(Int(txtSource), 1, UD(0))
                
    If R >= 100000 Then
        txtResult = "Error " & (R - 100000)
    Else
        txtResult = R
        txtDump.Text = "UD = (AddValue) " & vbCrLf
        Call HexDump(UD, 32)
    End If

End Sub

Private Sub cmdDeduct_Click()
    
    Dim PollData As String * 512
   
    Dim AI(64) As Byte
    Dim Tmp As String

'Concatenate the block info and add. info
    Tmp = txtBlockInfo & txtAddInfo
    
    For i = 0 To 6
        AI(i) = toDec(Mid(Tmp, i * 2 + 1, 2))
    Next i
    
    txtResult = "Requesting..."
    DoEvents
    R = Deduct(Int(txtSource), AI(0))
    
    If R >= 100000 Then
        txtResult = "Error " & (R - 100000)
    Else
        txtResult = R
        
        If AI(32) = 0 Then 'No autopay
            txtDump.Text = "UD = (Deduct) " & vbCrLf
            Call HexDump(AI, 32)
        Else        ' Autopay, 2x32 bytes
            txtDump.Text = "UD = (Autopay + Deduct) " & vbCrLf
            Call HexDump(AI, 64)
        End If
    End If

End Sub

Private Sub cmdDeferDeduct_Click(Index As Integer)
    
    Dim PollData As String * 512
   
    Dim AI(64) As Byte
    Dim Tmp As String

'Concatenate the block info and add. info
    Tmp = txtBlockInfo & txtAddInfo
    
    For i = 0 To 6
        AI(i) = toDec(Mid(Tmp, i * 2 + 1, 2))
    Next i
    
    txtResult = "Requesting..."
    DoEvents
    R = DeferDeduct(Index, Int(txtSource), AI(0))
    
    If R >= 100000 Then
        txtResult = "Error " & (R - 100000)
    Else
        If Index = 3 Then
            txtResult = R
            If AI(32) = 0 Then 'No autopay
                txtDump.Text = "UD = (Deduct) " & vbCrLf
                Call HexDump(AI, 32)
            Else        ' Autopay, 2x32 bytes
                txtDump.Text = "UD = (Autopay + Deduct) " & vbCrLf
                Call HexDump(AI, 64)
            End If
        Else
            txtResult = "Command Okay"
        End If
    End If

End Sub

Private Sub cmdFare_Click()
    R = TxnAmt(Int(txtSource), 10000, 0, 0)
    If R >= 100000 Then
        txtResult = "Error " & (R - 100000)
    Else
        txtResult = "Fare Set"
    End If
End Sub


Private Sub cmdFirmware_Click()
    txtResult = "Sending Firmware"
    DoEvents
    
    If txtFileName = "" Then txtFileName = "firmware.dat"
    R = FirmUpg(txtFileName)
    If R >= 100000 Then
        txtResult = "Error " & (R - 100000)
    Else
        txtResult = "Firmware succesfully sent"
    End If
End Sub

Private Sub CmdHouse_Click()
    R = HouseKeeping()
    If R >= 100000 Then
        txtResult = "Error " & (R - 100000)
    Else
        txtResult = "Housekeeping Okay"
    End If
  
End Sub

Private Sub cmdInit_Click()
    
    R = InitComm(Port, 0)
    
    If R >= 100000 Then
        txtResult = "Init Comm Error " & (R - 100000)
    Else
        txtResult = "Init Comm OKAY"
    End If
    
End Sub

Private Sub cmdLog_Click()
    Dim PollData As String * 512
    Dim Log() As String
    
    txtResult = "Polling..."
    DoEvents
    R = Poll(18, Int(txtTimeout), PollData)
    If R >= 100000 Then
        txtResult = "Error " & (R - 100000)
    Else
        txtResult = R
'Dump the returned comma seperated fields
        Log = Split(PollData, ",")
        idx = 3
        txtDump.Text = " SP| Amt|Transaction Date/Time| Mach|SP" & vbCrLf
        txtDump.Text = txtDump.Text & "---|----|---------------------|-----|----------" & vbCrLf
        For i = 1 To 10
            txtDump.Text = txtDump.Text & Format(Log(idx), "000") & "|"
            If (Log(idx + 1) > 0) Then
                txtDump.Text = txtDump.Text & Format(Log(idx + 1), "+000") & "|"
            Else
                txtDump.Text = txtDump.Text & Format(Log(idx + 1), "000") & "|"
            End If
            txtDump.Text = txtDump.Text & cvDate(Val(Log(idx + 2))) & "|"
            txtDump.Text = txtDump.Text & Format(Log(idx + 3), "00000") & "|"
            txtDump.Text = txtDump.Text & Log(idx + 4) & vbCrLf
            idx = idx + 5
        Next i
    End If

End Sub

Private Sub cmdPIN_Click()
    
    R = PIN(Int(txtSource), 0)
    If R >= 100000 Then
        txtResult = "Error " & (R - 100000)
    Else
        If R = 0 Then
            txtResult = "PIN matched"
        Else
            txtResult = "PIN mis-matched"
        End If
    End If
        
End Sub

Private Sub cmdPoll_Click()
    Dim PollData As String * 512
    
    txtResult = "Polling..."
    DoEvents
    R = Poll(1, Int(txtTimeout), PollData)
    If R = 100024 Then 'blocked
        Dim BlkUD(32) As Byte
        ' Convert the data from string to binary
        txtResult = "Card blocked"
        txtDump.Text = "Block UD" & vbCrLf
        For i = 1 To 32
            BlkUD(i - 1) = Asc(Mid(PollData, i, 1))
        Next i
        Call HexDump(BlkUD, 32)
        Exit Sub
    End If
    
    If R >= 100000 Then
        txtResult = "Error " & (R - 100000)
    Else
        Dim Log() As String
        
        Log = Split(PollData, ",")
        txtResult = R
        txtDump.Text = "Card ID = " & Log(0) & vbCrLf & "Patron  = " & Log(2) & vbCrLf
        txtDump.Text = txtDump.Text & PollData
    End If
End Sub


Private Sub cmdPortClose_Click()
    PortClose
End Sub

Private Sub cmdReset_Click()
    R = Reset()
End Sub

Private Sub cmdTimeVer_Click()
    Dim d As DevVerRec
    R = TimeVer(d)
    If R >= 100000 Then
        txtResult = "Error " & (R - 100000)
    Else
        txtResult = "Version Info retrieved " & vbCrLf
        txtDump.Text = "Company ID = " & d.CompID & vbCrLf
        txtDump.Text = txtDump.Text & "Device ID = " & d.DevID & vbCrLf
        txtDump.Text = txtDump.Text & "Operator ID = " & d.OperID & vbCrLf
        txtDump.Text = txtDump.Text & "Device Time = " & d.DevTime & vbCrLf
        txtDump.Text = txtDump.Text & "Key Version = " & d.KeyVer & vbCrLf
        txtDump.Text = txtDump.Text & "EOD Version = " & d.EODVer & vbCrLf
        txtDump.Text = txtDump.Text & "Blacklist Version = " & d.BLVer & vbCrLf
        txtDump.Text = txtDump.Text & "Firmware Version = " & d.FIRMVer & vbCrLf
        txtDump.Text = txtDump.Text & "CCHS Version = " & d.CCHSVer & vbCrLf
        txtDump.Text = txtDump.Text & "Location ID = " & d.CSSer & vbCrLf
    End If
    
End Sub

Private Sub cmdWriteID_Click()
    R = WriteID(Int(txtSource))
    If R >= 100000 Then
        txtResult = "Error " & (R - 100000)
        txtDump.Text = ""
    Else
        txtResult = ""
        txtDump.Text = "ID Wrote" & vbCrLf
    End If
    
End Sub

Private Sub cmdXFile_Click()
Dim XFileName As String * 128
    'Change the current directory to whatever
    R = XFile(XFileName)
    
    If R >= 100000 Then
        txtResult = "Error " & (R - 100000)
        txtDump.Text = ""
    Else
        txtResult = ""
        txtDump.Text = "Exchange File Name = " & vbCrLf & XFileName & vbCrLf
    End If

End Sub

Private Sub ChLoc()
    If Mid(txtCurDir, 2, 1) = ":" Then
        ChDrive (Left(txtCurDir, 2))
        ChDir (Mid(txtCurDir, 3))
    Else
        ChDir txtCurDir
    End If
End Sub

Private Sub Form_Load()
' Change this setting for different communication port
    Dim Port As Integer
    
    DoEvents
    DoEvents
    DoEvents
    DoEvents
    DoEvents
    Cmdline = Command()
    If Len(Cmdline) = 0 Then
        Port = 0
    Else
        Port = Int(Cmdline)
    End If
    
    R = InitComm(0, 0)
    
    If R >= 100000 Then
        txtResult = "Init Comm Error " & (R - 100000)
    Else
        txtResult = "Init Comm OKAY"
    End If
    
    
    ChLoc
End Sub

Private Sub txtAddInfo_LostFocus()
'Check the length of the field
If Len(txtAddInfo) <> 4 Then
        MsgBox "Additional Info must be a two byte HEX"
        txtAddInfo.SetFocus
    End If
    txtAddInfo = Format$(txtAddInfo, ">")
End Sub

Private Sub txtBlockInfo_LostFocus()
'Check the length of the field
    If Len(txtBlockInfo) <> 10 Then
        MsgBox "Block Info must be a five byte HEX"
        txtAddInfo.SetFocus
    End If
    txtBlockInfo = Format$(txtBlockInfo, ">")
End Sub

Private Sub txtCurDir_LostFocus()
    ChLoc
End Sub

