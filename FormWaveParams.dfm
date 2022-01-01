object frmWaveParameters: TfrmWaveParameters
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Shot detection parameters'
  ClientHeight = 202
  ClientWidth = 269
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label15: TLabel
    Left = 32
    Top = 27
    Width = 76
    Height = 13
    Caption = 'Confidence (%)'
  end
  object Label14: TLabel
    Left = 144
    Top = 26
    Width = 83
    Height = 13
    Caption = 'Min duration (ms)'
  end
  object Label1: TLabel
    Left = 32
    Top = 82
    Width = 94
    Height = 13
    Caption = 'Min detect dist (ms)'
  end
  object edtPeakDetConf: TEdit
    Left = 32
    Top = 42
    Width = 91
    Height = 21
    Alignment = taRightJustify
    NumbersOnly = True
    TabOrder = 0
    Text = '80'
    TextHint = '10-100 %'
  end
  object edtPeakDetMinDuration: TEdit
    Left = 144
    Top = 42
    Width = 91
    Height = 21
    Alignment = taRightJustify
    NumbersOnly = True
    TabOrder = 1
    Text = '70'
    TextHint = '20-500 ms'
  end
  object Button1: TButton
    Left = 40
    Top = 144
    Width = 75
    Height = 25
    Action = actOK
    TabOrder = 2
  end
  object Button2: TButton
    Left = 152
    Top = 144
    Width = 75
    Height = 25
    Action = actCancel
    TabOrder = 3
  end
  object edtPeakDMinDetectionTimeDistance: TEdit
    Left = 32
    Top = 98
    Width = 91
    Height = 21
    Alignment = taRightJustify
    NumbersOnly = True
    TabOrder = 4
    Text = '200'
    TextHint = '0-1000 ms'
  end
  object ActionList1: TActionList
    Left = 176
    Top = 72
    object actOK: TAction
      Caption = 'OK'
      OnExecute = actOKExecute
      OnUpdate = actOKUpdate
    end
    object actCancel: TAction
      Caption = 'Cancel'
      OnExecute = actCancelExecute
    end
  end
end
