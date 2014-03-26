object Form1: TForm1
  Left = 385
  Top = 106
  Width = 360
  Height = 237
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 10
    Top = 9
    Width = 26
    Height = 13
    Caption = 'Login'
  end
  object Label2: TLabel
    Left = 10
    Top = 32
    Width = 46
    Height = 13
    Caption = 'Password'
  end
  object Label3: TLabel
    Left = 10
    Top = 56
    Width = 16
    Height = 13
    Caption = 'File'
  end
  object Label4: TLabel
    Left = 10
    Top = 83
    Width = 48
    Height = 13
    Caption = 'Response'
  end
  object Button1: TButton
    Left = 64
    Top = 181
    Width = 75
    Height = 25
    Caption = 'Send'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 154
    Top = 181
    Width = 75
    Height = 25
    Caption = 'Dowlnoad'
    TabOrder = 1
    OnClick = Button2Click
  end
  object Edit1: TEdit
    Left = 64
    Top = 5
    Width = 250
    Height = 21
    TabOrder = 2
    Text = 'Edit1'
  end
  object Edit2: TEdit
    Left = 64
    Top = 28
    Width = 250
    Height = 21
    TabOrder = 3
    Text = 'Edit2'
  end
  object Edit3: TEdit
    Left = 64
    Top = 52
    Width = 250
    Height = 21
    TabOrder = 4
    Text = 'Edit3'
  end
  object Memo1: TMemo
    Left = 64
    Top = 83
    Width = 250
    Height = 65
    Lines.Strings = (
      'Memo1')
    TabOrder = 5
  end
  object ProgressBar1: TProgressBar
    Left = 65
    Top = 156
    Width = 249
    Height = 16
    Min = 0
    Max = 100
    TabOrder = 6
  end
  object Button3: TButton
    Left = 239
    Top = 181
    Width = 75
    Height = 25
    Caption = 'Refresh'
    TabOrder = 7
  end
  object OpenDialog1: TOpenDialog
    Top = 184
  end
  object IdHttpForm: TIdHTTP
    OnWork = IdHttpFormWork
    OnWorkBegin = IdHttpFormWorkBegin
    OnWorkEnd = IdHttpFormWorkEnd
    Request.Accept = 'text/html, image/gif, image/jpeg, */*'
    Request.ContentLength = 0
    Request.ContentRangeEnd = 0
    Request.ContentRangeStart = 0
    Request.ContentType = 'multipart/form-data'
    Request.ProxyPort = 0
    Request.UserAgent = 'Mozilla/3.0 (compatible; Indy Library)'
    Left = 32
    Top = 184
  end
end
