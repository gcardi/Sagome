object frmMain: TfrmMain
  Left = 0
  Top = 0
  Caption = 'frmMain'
  ClientHeight = 726
  ClientWidth = 958
  Color = clBtnFace
  Constraints.MinHeight = 600
  Constraints.MinWidth = 970
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  ShowHint = True
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 294
    Width = 958
    Height = 3
    Cursor = crVSplit
    Align = alTop
    ResizeStyle = rsUpdate
    ExplicitLeft = -8
    ExplicitTop = 223
    ExplicitWidth = 664
  end
  object pnlLog: TPanel
    Left = 0
    Top = 438
    Width = 958
    Height = 269
    Margins.Left = 8
    Margins.Top = 0
    Margins.Right = 8
    Margins.Bottom = 8
    Align = alClient
    BevelOuter = bvNone
    Caption = 'pnlLog'
    Constraints.MinHeight = 100
    ShowCaption = False
    TabOrder = 0
    inline frmeLog1: TfrmeLog
      Left = 0
      Top = 0
      Width = 958
      Height = 269
      Align = alClient
      TabOrder = 0
      ExplicitWidth = 958
      ExplicitHeight = 269
      inherited RichEdit1: TRichEdit
        Width = 958
        Height = 252
        ScrollBars = ssBoth
        ExplicitWidth = 958
        ExplicitHeight = 252
      end
      inherited Panel2: TPanel
        Width = 958
        ExplicitWidth = 958
      end
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 707
    Width = 958
    Height = 19
    AutoHint = True
    Panels = <>
    SimplePanel = True
  end
  object pnlTrials: TPanel
    Left = 0
    Top = 297
    Width = 958
    Height = 141
    Align = alTop
    BevelOuter = bvNone
    Caption = 'pnlTrials'
    ShowCaption = False
    TabOrder = 2
    object Panel6: TPanel
      Left = 0
      Top = 0
      Width = 958
      Height = 17
      Align = alTop
      Caption = 'Trials'
      TabOrder = 0
    end
    object Panel3: TPanel
      Left = 0
      Top = 17
      Width = 664
      Height = 124
      Align = alClient
      BevelOuter = bvNone
      Caption = 'Panel3'
      ShowCaption = False
      TabOrder = 1
      object PageControl1: TPageControl
        Left = 0
        Top = 0
        Width = 625
        Height = 124
        ActivePage = tbshtModbus
        Align = alLeft
        TabOrder = 0
        object tbshtPGCMirato: TTabSheet
          Caption = 'PGC Mirato'
          ImageIndex = 2
          object Button2: TButton
            Left = 14
            Top = 14
            Width = 155
            Height = 25
            Action = actGareProvaPGCMiratoStart
            ParentShowHint = False
            ShowHint = False
            TabOrder = 0
          end
          object Button17: TButton
            Left = 183
            Top = 14
            Width = 155
            Height = 25
            Action = actGarePrimaPGCMiratoStart
            ParentShowHint = False
            ShowHint = False
            TabOrder = 1
          end
          object Button18: TButton
            Left = 14
            Top = 54
            Width = 155
            Height = 25
            Action = actGareProssimaPGCMiratoStart
            ParentShowHint = False
            ShowHint = False
            TabOrder = 2
          end
        end
        object tbshtPGCCelere: TTabSheet
          Caption = 'PGC Celere'
          ImageIndex = 3
          object Button6: TButton
            Left = 14
            Top = 14
            Width = 155
            Height = 25
            Action = actGareProvaPGCCelereStart
            ParentShowHint = False
            ShowHint = False
            TabOrder = 0
          end
          object Button15: TButton
            Left = 183
            Top = 14
            Width = 155
            Height = 25
            Action = actGarePrimaPGCCelereStart
            ParentShowHint = False
            ShowHint = False
            TabOrder = 1
          end
          object Button16: TButton
            Left = 14
            Top = 54
            Width = 155
            Height = 25
            Action = actGareProssimaPGCCelereStart
            ParentShowHint = False
            ShowHint = False
            TabOrder = 2
          end
        end
        object tbshtPS150sec: TTabSheet
          Caption = 'PS 150"'
          ImageIndex = 6
          object Button9: TButton
            Left = 14
            Top = 14
            Width = 155
            Height = 25
            Action = actGareProvaPS150
            ParentShowHint = False
            ShowHint = False
            TabOrder = 0
          end
          object Button21: TButton
            Left = 183
            Top = 14
            Width = 155
            Height = 25
            Action = actGarePrimaPS150
            ParentShowHint = False
            ShowHint = False
            TabOrder = 1
          end
          object Button22: TButton
            Left = 14
            Top = 54
            Width = 155
            Height = 25
            Action = actGareProssimaPS150
            ParentShowHint = False
            ShowHint = False
            TabOrder = 2
          end
        end
        object tbshtPS20sec: TTabSheet
          Caption = 'PS 20"'
          ImageIndex = 5
          object Button10: TButton
            Left = 14
            Top = 14
            Width = 155
            Height = 25
            Action = actGarePrimaPS20
            ParentShowHint = False
            ShowHint = False
            TabOrder = 0
          end
          object Button20: TButton
            Left = 14
            Top = 54
            Width = 155
            Height = 25
            Action = actGareProssimaPS20
            ParentShowHint = False
            ShowHint = False
            TabOrder = 1
          end
        end
        object tbshtPS10sec: TTabSheet
          Caption = 'PS 10"'
          ImageIndex = 4
          object Button11: TButton
            Left = 14
            Top = 14
            Width = 155
            Height = 25
            Action = actGarePrimaPS10
            ParentShowHint = False
            ShowHint = False
            TabOrder = 0
          end
          object Button19: TButton
            Left = 14
            Top = 54
            Width = 155
            Height = 25
            Action = actGareProssimaPS10
            ParentShowHint = False
            ShowHint = False
            TabOrder = 1
          end
        end
        object tbshtPA8sec: TTabSheet
          Caption = 'PA 8"'
          ImageIndex = 9
          object Button12: TButton
            Left = 14
            Top = 14
            Width = 155
            Height = 25
            Action = actGareProvaPA8
            ParentShowHint = False
            ShowHint = False
            TabOrder = 0
          end
          object Button25: TButton
            Left = 14
            Top = 54
            Width = 155
            Height = 25
            Action = actGareProssimaPA8
            ParentShowHint = False
            ShowHint = False
            TabOrder = 1
          end
          object Button26: TButton
            Left = 183
            Top = 14
            Width = 155
            Height = 25
            Action = actGarePrimaPA8
            ParentShowHint = False
            ShowHint = False
            TabOrder = 2
          end
        end
        object tbshtPA6sec: TTabSheet
          Caption = 'PA 6"'
          ImageIndex = 8
          object Button13: TButton
            Left = 14
            Top = 14
            Width = 155
            Height = 25
            Action = actGarePrimaPA6
            ParentShowHint = False
            ShowHint = False
            TabOrder = 0
          end
          object Button24: TButton
            Left = 14
            Top = 54
            Width = 155
            Height = 25
            Action = actGareProssimaPA6
            ParentShowHint = False
            ShowHint = False
            TabOrder = 1
          end
        end
        object tbshtPA4sec: TTabSheet
          Caption = 'PA 4"'
          ImageIndex = 7
          object Button14: TButton
            Left = 14
            Top = 14
            Width = 155
            Height = 25
            Action = actGarePrimaPA4
            ParentShowHint = False
            ShowHint = False
            TabOrder = 0
          end
          object Button23: TButton
            Left = 14
            Top = 54
            Width = 155
            Height = 25
            Action = actGareProssimaPA4
            ParentShowHint = False
            ShowHint = False
            TabOrder = 1
          end
        end
        object tbshtModbus: TTabSheet
          Caption = 'Modbus'
          TabVisible = False
          inline frmeModbusFunctions1: TfrmeModbusFunctions
            Left = 0
            Top = 0
            Width = 617
            Height = 96
            Align = alClient
            TabOrder = 0
            ExplicitWidth = 617
            ExplicitHeight = 96
            inherited Panel4: TPanel
              Width = 617
              Caption = 'Functions'
              ExplicitWidth = 617
            end
            inherited pgctrlFunctions: TPageControl
              Width = 617
              Height = 79
              ExplicitWidth = 617
              ExplicitHeight = 79
              inherited tbshrFnReadHoldingRegisters: TTabSheet
                ExplicitWidth = 609
                ExplicitHeight = 51
                inherited Button2: TButton
                  Action = actFnReadHoldingRegisters
                  Caption = 'Read'
                end
              end
              inherited tbshrFnReadInputRegisters: TTabSheet
                ExplicitWidth = 609
                ExplicitHeight = 51
                inherited Button6: TButton
                  Action = actFnReadInputRegisters
                  Caption = 'Read'
                end
              end
              inherited tbshtFnPresetSingleRegister: TTabSheet
                ExplicitWidth = 609
                ExplicitHeight = 51
                inherited Button3: TButton
                  Action = actFnPresetSingleRegister
                  Caption = 'Preset'
                end
              end
              inherited tbshtFnPresetMultipleRegisters: TTabSheet
                ExplicitWidth = 609
                ExplicitHeight = 51
                inherited Button5: TButton
                  Action = actFnPresetMultipleRegisters
                end
                inherited edtPresetMultipleRegistersData: TEdit
                  Width = 287
                end
              end
            end
          end
        end
      end
    end
    object pnlStopwatch: TPanel
      Left = 664
      Top = 17
      Width = 294
      Height = 124
      Align = alRight
      BevelOuter = bvNone
      Caption = 'pnlStopwatch'
      ShowCaption = False
      TabOrder = 2
      DesignSize = (
        294
        124)
      object lblStopwatch: TLabel
        Left = -9
        Top = 32
        Width = 261
        Height = 82
        Alignment = taCenter
        Anchors = [akTop, akRight]
        AutoSize = False
        Caption = '00:00:0'
        Color = clBlack
        Constraints.MaxHeight = 148
        Constraints.MaxWidth = 512
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -64
        Font.Name = 'Arial'
        Font.Style = []
        ParentColor = False
        ParentFont = False
        Transparent = False
        Layout = tlCenter
      end
    end
  end
  object pnlTop: TPanel
    Left = 0
    Top = 0
    Width = 958
    Height = 294
    Align = alTop
    Caption = 'pnlTop'
    Constraints.MinHeight = 229
    ShowCaption = False
    TabOrder = 3
    object PageControl2: TPageControl
      Left = 1
      Top = 1
      Width = 956
      Height = 292
      ActivePage = TabSheet1
      Align = alClient
      TabOrder = 0
      object TabSheet1: TTabSheet
        Caption = 'Shooting targets'
        object Label3: TLabel
          Left = 18
          Top = 107
          Width = 16
          Height = 13
          Alignment = taRightJustify
          Caption = '1-5'
        end
        object Label4: TLabel
          Left = 12
          Top = 140
          Width = 22
          Height = 13
          Alignment = taRightJustify
          Caption = '6-10'
        end
        object PaintBox6_10: TPaintBox
          Tag = 1
          Left = 163
          Top = 139
          Width = 174
          Height = 17
          OnPaint = PaintBox1_5Paint
        end
        object PaintBox1_5: TPaintBox
          Left = 163
          Top = 106
          Width = 174
          Height = 17
          OnPaint = PaintBox1_5Paint
        end
        object Label8: TLabel
          Left = 131
          Top = 107
          Width = 23
          Height = 13
          Alignment = taRightJustify
          Caption = 'Outs'
        end
        object Label9: TLabel
          Left = 131
          Top = 140
          Width = 23
          Height = 13
          Alignment = taRightJustify
          Caption = 'Outs'
        end
        object GroupBox1: TGroupBox
          Left = 195
          Top = 3
          Width = 169
          Height = 54
          Caption = 'Communication'
          TabOrder = 0
          object Button1: TButton
            Left = 13
            Top = 19
            Width = 65
            Height = 25
            Action = actOpen
            TabOrder = 0
          end
          object Button4: TButton
            Left = 89
            Top = 19
            Width = 66
            Height = 25
            Action = actClose
            TabOrder = 1
          end
        end
        object ToggleSwitch1: TToggleSwitch
          Left = 40
          Top = 104
          Width = 72
          Height = 20
          Action = actGareEnb1_5
          FrameColor = clWindowFrame
          TabOrder = 1
          ThumbColor = cl3DDkShadow
        end
        object ToggleSwitch2: TToggleSwitch
          Left = 40
          Top = 137
          Width = 72
          Height = 20
          Action = actGareEnb6_10
          FrameColor = clWindowFrame
          TabOrder = 2
          ThumbColor = cl3DDkShadow
        end
        object GroupBox2: TGroupBox
          Left = 12
          Top = 3
          Width = 169
          Height = 87
          Caption = 'Manual'
          TabOrder = 3
          object Button3: TButton
            Left = 13
            Top = 20
            Width = 66
            Height = 25
            Action = actGareResetCycle
            ParentShowHint = False
            ShowHint = False
            TabOrder = 0
          end
          object Button7: TButton
            Left = 13
            Top = 51
            Width = 66
            Height = 25
            Action = actGareApertura
            ParentShowHint = False
            ShowHint = False
            TabOrder = 1
          end
          object Button8: TButton
            Left = 90
            Top = 51
            Width = 66
            Height = 25
            Action = actGareChiusura
            ParentShowHint = False
            ShowHint = False
            TabOrder = 2
          end
        end
        object Button5: TButton
          Left = 102
          Top = 23
          Width = 66
          Height = 25
          Action = actGareStop
          ParentShowHint = False
          ShowHint = False
          TabOrder = 4
        end
      end
      object TabSheet2: TTabSheet
        Caption = 'Protocol'
        ImageIndex = 1
        object Panel5: TPanel
          AlignWithMargins = True
          Left = 16
          Top = 16
          Width = 916
          Height = 105
          Margins.Left = 16
          Margins.Top = 16
          Margins.Right = 16
          Align = alTop
          BevelOuter = bvNone
          Caption = 'Panel5'
          ShowCaption = False
          TabOrder = 0
          object pgctrlProtocolSettings: TPageControl
            Left = 0
            Top = 49
            Width = 916
            Height = 56
            ActivePage = tbshtProtocolDummySettings
            Align = alClient
            Style = tsButtons
            TabOrder = 0
            object tbshtProtocolSerialSettings: TTabSheet
              Caption = 'tbshtProtocolSerialSettings'
              TabVisible = False
              inline frmeSerialSettings1: TfrmeSerialSettings
                Left = 3
                Top = 1
                Width = 554
                Height = 37
                AutoSize = True
                TabOrder = 0
                ExplicitLeft = 3
                ExplicitTop = 1
                inherited cmboxStopBits: TComboBox
                  TabOrder = 3
                end
                inherited cmboxDataBits: TComboBox
                  TabOrder = 4
                end
                inherited checkboxCancelTXEcho: TCheckBox
                  TabOrder = 2
                end
              end
            end
            object tbshtProtocolTCPIPSettings: TTabSheet
              Caption = 'tbshtProtocolTCPIPSettings'
              ImageIndex = 1
              TabVisible = False
              object Label1: TLabel
                Left = 3
                Top = 2
                Width = 22
                Height = 13
                Caption = 'Host'
              end
              object Label2: TLabel
                Left = 136
                Top = 2
                Width = 20
                Height = 13
                Caption = 'Port'
              end
              object edtTCPIPHost: TEdit
                Left = 3
                Top = 18
                Width = 121
                Height = 21
                TabOrder = 0
                Text = 'localhost'
              end
              object edtTCPIPPort: TEdit
                Left = 136
                Top = 18
                Width = 49
                Height = 21
                Alignment = taRightJustify
                NumbersOnly = True
                TabOrder = 1
                Text = '502'
              end
            end
            object tbshtProtocolDummySettings: TTabSheet
              Caption = 'tbshtProtocolDummySettings'
              ImageIndex = 2
              TabVisible = False
            end
          end
          object Panel1: TPanel
            Left = 0
            Top = 0
            Width = 916
            Height = 49
            Align = alTop
            BevelOuter = bvNone
            Caption = 'Panel1'
            ShowCaption = False
            TabOrder = 1
            object Label5: TLabel
              Left = 0
              Top = 1
              Width = 39
              Height = 13
              Caption = 'Protocol'
            end
            object Label6: TLabel
              Left = 144
              Top = 0
              Width = 40
              Height = 13
              Caption = 'Slave ID'
            end
            object Label7: TLabel
              Left = 208
              Top = 0
              Width = 70
              Height = 13
              Caption = 'Transaction ID'
            end
            object cboxAutoIncTransactionID: TCheckBox
              Left = 296
              Top = 18
              Width = 145
              Height = 17
              Caption = 'Auto inc Transaction ID'
              Checked = True
              State = cbChecked
              TabOrder = 0
            end
            object comboboxProtocol: TComboBox
              Left = 0
              Top = 17
              Width = 129
              Height = 21
              Style = csDropDownList
              TabOrder = 1
              OnChange = comboboxProtocolChange
            end
            object edtSlaveId: TEdit
              Left = 144
              Top = 16
              Width = 49
              Height = 21
              Alignment = taRightJustify
              NumbersOnly = True
              TabOrder = 2
              Text = '1'
            end
            object edtTransactionID: TEdit
              Left = 208
              Top = 16
              Width = 70
              Height = 21
              Alignment = taRightJustify
              NumbersOnly = True
              TabOrder = 3
              Text = '0'
            end
          end
        end
      end
      object tbshtMic: TTabSheet
        Caption = 'Mic'
        ImageIndex = 2
        DesignSize = (
          948
          264)
        object Label10: TLabel
          Left = 13
          Top = 48
          Width = 32
          Height = 13
          Caption = 'Device'
        end
        object pboxFreqCuts: TPaintBox
          Left = 3
          Top = 229
          Width = 381
          Height = 34
          Anchors = [akLeft, akBottom]
          OnMouseDown = pboxFreqCutsMouseDown
          OnMouseMove = pboxFreqCutsMouseMove
          OnMouseUp = pboxFreqCutsMouseUp
          OnPaint = pboxFreqCutsPaint
        end
        object comboboxAudioSources: TComboBox
          Left = 13
          Top = 64
          Width = 229
          Height = 21
          Style = csDropDownList
          TabOrder = 0
        end
        object Button27: TButton
          Left = 13
          Top = 16
          Width = 108
          Height = 25
          Action = actWaveStartListening
          TabOrder = 1
        end
        object Button28: TButton
          Left = 133
          Top = 16
          Width = 108
          Height = 25
          Action = actWaveStopListening
          TabOrder = 2
        end
        object pgctrlWaveViewer: TPageControl
          Left = 436
          Top = 10
          Width = 497
          Height = 246
          ActivePage = tbshtViewerFreq
          Anchors = [akLeft, akTop, akBottom]
          Constraints.MaxWidth = 640
          TabOrder = 3
          object tbshtViewerFreq: TTabSheet
            Caption = 'Frequency domain'
            object chartFreq: TChart
              Left = 0
              Top = 0
              Width = 489
              Height = 218
              AllowPanning = pmNone
              Title.Text.Strings = (
                'Freq (Hz)')
              BottomAxis.Automatic = False
              BottomAxis.AutomaticMaximum = False
              BottomAxis.AutomaticMinimum = False
              BottomAxis.LogarithmicBase = 2.000000000000000000
              BottomAxis.Maximum = 11025.000000000000000000
              BottomAxis.Minimum = 60.000000000000000000
              LeftAxis.Automatic = False
              LeftAxis.AutomaticMaximum = False
              LeftAxis.AutomaticMinimum = False
              LeftAxis.LabelsSeparation = 20
              LeftAxis.Maximum = 10.000000000000000000
              LeftAxis.Minimum = -100.000000000000000000
              LeftAxis.Title.Caption = 'dB'
              LeftAxis.Title.Visible = False
              Panning.MouseWheel = pmwNone
              RightAxis.Visible = False
              View3D = False
              Zoom.Allow = False
              Align = alClient
              BevelOuter = bvNone
              ParentColor = True
              TabOrder = 0
              DefaultCanvas = 'TGDIPlusCanvas'
              ColorPaletteIndex = 13
              object SeriesFreqCuts: TAreaSeries
                Legend.Visible = False
                SeriesColor = 8454143
                ShowInLegend = False
                AreaChartBrush.Color = clGray
                AreaChartBrush.BackColor = clDefault
                ClickableLine = False
                DrawArea = True
                Pointer.InflateMargins = True
                Pointer.Style = psRectangle
                Pointer.Visible = False
                Transparency = 72
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.Name = 'Y'
                YValues.Order = loNone
                Data = {
                  0004000000000000000000000000000000000000000000000000000000000000
                  0000000000}
                Detail = {0000000000}
              end
              object SeriesFreq1: TLineSeries
                Legend.Visible = False
                SeriesColor = clBlue
                ShowInLegend = False
                Brush.BackColor = clDefault
                ClickableLine = False
                Pointer.Brush.Gradient.EndColor = 10708548
                Pointer.Gradient.EndColor = 10708548
                Pointer.InflateMargins = True
                Pointer.Style = psRectangle
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.Name = 'Y'
                YValues.Order = loNone
              end
              object SeriesFreq2: TLineSeries
                Legend.Visible = False
                Active = False
                SeriesColor = clBlue
                ShowInLegend = False
                Brush.BackColor = clDefault
                ClickableLine = False
                Pointer.InflateMargins = True
                Pointer.Style = psRectangle
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.Name = 'Y'
                YValues.Order = loNone
              end
              object SeriesdBThreshold: TLineSeries
                Legend.Visible = False
                SeriesColor = clRed
                ShowInLegend = False
                Brush.BackColor = clDefault
                ClickableLine = False
                Pointer.InflateMargins = True
                Pointer.Style = psRectangle
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.Name = 'Y'
                YValues.Order = loNone
                Data = {000200000000000000000034C000000000000034C0}
                Detail = {0000000000}
              end
            end
          end
          object tbshtViewerTime: TTabSheet
            Caption = 'Time domain'
            ImageIndex = 1
            object chartTime: TChart
              Left = 0
              Top = 0
              Width = 489
              Height = 218
              Title.Text.Strings = (
                'Time (ms)')
              BottomAxis.Automatic = False
              BottomAxis.AutomaticMaximum = False
              BottomAxis.AutomaticMinimum = False
              BottomAxis.LogarithmicBase = 2.000000000000000000
              BottomAxis.Maximum = 512.000000000000000000
              LeftAxis.Automatic = False
              LeftAxis.AutomaticMaximum = False
              LeftAxis.AutomaticMinimum = False
              LeftAxis.Maximum = 1.000000000000000000
              LeftAxis.Minimum = -1.000000000000000000
              RightAxis.Visible = False
              View3D = False
              Zoom.Allow = False
              Align = alClient
              BevelOuter = bvNone
              ParentColor = True
              TabOrder = 0
              DefaultCanvas = 'TGDIPlusCanvas'
              ColorPaletteIndex = 13
              object SeriesTime1: TLineSeries
                Legend.Visible = False
                SeriesColor = clBlue
                ShowInLegend = False
                Brush.BackColor = clDefault
                ClickableLine = False
                Pointer.Brush.Gradient.EndColor = 10708548
                Pointer.Gradient.EndColor = 10708548
                Pointer.InflateMargins = True
                Pointer.Style = psRectangle
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.Name = 'Y'
                YValues.Order = loNone
                Data = {
                  001900000000000000007062400000000000205C400000000000001440000000
                  00006058400000000000A05E4000000000003066400000000000C04C40000000
                  0000605D40000000000000594000000000000059400000000000406A40000000
                  0000A0644000000000005069400000000000F064400000000000404F40000000
                  0000003E400000000000803B400000000000205C400000000000001E40000000
                  0000405A400000000000806B4000000000003071400000000000987740000000
                  0000707C400000000000987C40}
                Detail = {0000000000}
              end
              object SeriesTime2: TLineSeries
                Legend.Visible = False
                Active = False
                SeriesColor = clBlue
                ShowInLegend = False
                Brush.BackColor = clDefault
                ClickableLine = False
                Pointer.Brush.Gradient.EndColor = 10708548
                Pointer.Gradient.EndColor = 10708548
                Pointer.InflateMargins = True
                Pointer.Style = psRectangle
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.Name = 'Y'
                YValues.Order = loNone
              end
            end
          end
        end
        object pnlThreshold: TPanel
          Left = 353
          Top = 63
          Width = 71
          Height = 167
          Anchors = [akLeft, akTop, akBottom]
          BevelOuter = bvNone
          Caption = 'pnlThreshold'
          ShowCaption = False
          TabOrder = 4
          object Label11: TLabel
            Left = 0
            Top = 0
            Width = 71
            Height = 13
            Align = alTop
            Alignment = taCenter
            Caption = 'Threshold'
            ExplicitWidth = 47
          end
          object lblThreshold: TLabel
            Left = 0
            Top = 13
            Width = 71
            Height = 13
            Align = alTop
            Alignment = taCenter
            AutoSize = False
            Caption = '-20 dB'
            ExplicitLeft = 9
            ExplicitTop = 28
            ExplicitWidth = 51
          end
          object Panel4: TPanel
            Left = 0
            Top = 26
            Width = 71
            Height = 141
            Align = alClient
            BevelOuter = bvNone
            Caption = 'Panel4'
            FullRepaint = False
            ShowCaption = False
            TabOrder = 0
            object pboxSpectrogramGradientIndicator: TPaintBox
              Left = 0
              Top = 0
              Width = 13
              Height = 141
              Align = alLeft
              OnMouseDown = pboxSpectrogramGradientIndicatorMouseDown
              OnMouseMove = pboxSpectrogramGradientIndicatorMouseMove
              OnMouseUp = pboxSpectrogramGradientIndicatorMouseUp
              OnPaint = pboxSpectrogramGradientIndicatorPaint
              ExplicitHeight = 174
            end
            object imgSpectrogramGradient: TImage
              AlignWithMargins = True
              Left = 15
              Top = 6
              Width = 17
              Height = 129
              Margins.Left = 2
              Margins.Top = 6
              Margins.Right = 2
              Margins.Bottom = 6
              Align = alLeft
              Stretch = True
              ExplicitHeight = 82
            end
            object Panel7: TPanel
              Left = 34
              Top = 0
              Width = 37
              Height = 141
              Align = alClient
              BevelOuter = bvNone
              Caption = 'Panel7'
              ShowCaption = False
              TabOrder = 0
              object Label13: TLabel
                Left = 0
                Top = 0
                Width = 37
                Height = 13
                Align = alTop
                Caption = '0dB'
                ExplicitWidth = 18
              end
              object lblFloor_dB: TLabel
                AlignWithMargins = True
                Left = 0
                Top = 127
                Width = 37
                Height = 13
                Margins.Left = 0
                Margins.Top = 0
                Margins.Right = 0
                Margins.Bottom = 1
                Align = alBottom
                Caption = '0dB'
                ExplicitWidth = 18
              end
            end
          end
        end
        object pnlSpectrogram: TPanel
          Left = 13
          Top = 96
          Width = 337
          Height = 129
          Anchors = [akLeft, akTop, akBottom]
          BevelKind = bkFlat
          BevelOuter = bvNone
          Caption = 'pnlSpectrogram'
          FullRepaint = False
          ShowCaption = False
          TabOrder = 5
          OnResize = pnlSpectrogramResize
          object pboxSpectrogram: TPaintBox
            Left = 34
            Top = 16
            Width = 256
            Height = 109
            Align = alClient
            OnPaint = pboxSpectrogramPaint
            ExplicitLeft = 46
            ExplicitTop = 17
            ExplicitWidth = 241
            ExplicitHeight = 111
          end
          object Panel2: TPanel
            Left = 0
            Top = 0
            Width = 333
            Height = 16
            Align = alTop
            BevelOuter = bvNone
            Caption = 'Spectrogram'
            TabOrder = 0
          end
          object pnlTime: TPanel
            AlignWithMargins = True
            Left = 291
            Top = 16
            Width = 42
            Height = 109
            Margins.Left = 1
            Margins.Top = 0
            Margins.Right = 0
            Margins.Bottom = 0
            Align = alRight
            BevelOuter = bvNone
            Caption = 'pnlTime'
            Color = clBlack
            ParentBackground = False
            ShowCaption = False
            TabOrder = 1
            object Label12: TLabel
              AlignWithMargins = True
              Left = 2
              Top = 93
              Width = 40
              Height = 13
              Margins.Left = 2
              Margins.Top = 0
              Margins.Right = 0
              Align = alBottom
              Caption = #8595'0 s'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clAqua
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              ExplicitWidth = 20
            end
            object lblSpectrogramDuration: TLabel
              AlignWithMargins = True
              Left = 2
              Top = 0
              Width = 40
              Height = 13
              Margins.Left = 2
              Margins.Top = 0
              Margins.Right = 0
              Align = alTop
              Caption = #8593'0 s'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clAqua
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              ExplicitWidth = 20
            end
          end
          object pnlPeaksTimepoint: TPanel
            AlignWithMargins = True
            Left = 0
            Top = 16
            Width = 33
            Height = 109
            Margins.Left = 0
            Margins.Top = 0
            Margins.Right = 1
            Margins.Bottom = 0
            Align = alLeft
            BevelOuter = bvNone
            Caption = 'pnlPeaksTimepoint'
            Color = clNavy
            FullRepaint = False
            ParentBackground = False
            ShowCaption = False
            TabOrder = 2
            object pboxPeaksTimepoint: TPaintBox
              Left = 0
              Top = 0
              Width = 33
              Height = 109
              Align = alClient
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -9
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              OnPaint = pboxPeaksTimepointPaint
              ExplicitWidth = 28
            end
          end
        end
        object Button29: TButton
          Left = 253
          Top = 16
          Width = 108
          Height = 25
          Action = actWaveSetParameters
          TabOrder = 6
        end
      end
    end
  end
  object ActionManager1: TActionManager
    OnExecute = ActionManager1Execute
    OnUpdate = ActionManager1Update
    Left = 432
    Top = 320
    StyleName = 'Platform Default'
    object actGareProssimaPA4: TAction
      Category = 'GarePistolaAutomatica'
      Caption = 'Prossima serie PA 4"'
      OnExecute = actGareProssimaPA4Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareProssimaPS10: TAction
      Category = 'GarePistolaStandard'
      Caption = 'Prossima serie PS 10"'
      OnExecute = actGareProssimaPS10Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGarePrimaPA8: TAction
      Category = 'GarePistolaAutomatica'
      Caption = 'Prima serie PA 8"'
      OnExecute = actGarePrimaPA8Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareProssimaPA6: TAction
      Category = 'GarePistolaAutomatica'
      Caption = 'Prossima serie PA 6"'
      OnExecute = actGareProssimaPA6Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareProvaPGCMiratoStart: TAction
      Category = 'GarePGCMirato'
      Caption = 'Serie di prova PGC Mirato'
      Hint = 'Serie di prova PGC Mirato|Chiuso per 7" e poi aperto per 300"'
      OnExecute = actGareProvaPGCMiratoStartExecute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareProssimaPA8: TAction
      Category = 'GarePistolaAutomatica'
      Caption = 'Prossima serie PA 8"'
      OnExecute = actGareProssimaPA8Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareProssimaPS20: TAction
      Category = 'GarePistolaStandard'
      Caption = 'Prossima serie PS 20"'
      OnExecute = actGareProssimaPS20Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareProssimaPGCMiratoStart: TAction
      Category = 'GarePGCMirato'
      Caption = 'Prossima serie PGC Mirato'
      Hint = 'Prossima serie  PGC Mirato|Chiuso per 7" e poi aperto per 300"'
      OnExecute = actGareProssimaPGCMiratoStartExecute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGarePrimaPS150: TAction
      Category = 'GarePistolaStandard'
      Caption = 'Prima serie PS 150"'
      OnExecute = actGarePrimaPS150Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareProssimaPS150: TAction
      Category = 'GarePistolaStandard'
      Caption = 'Prossima serie PS 150"'
      OnExecute = actGareProssimaPS150Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGarePrimaPGCCelereStart: TAction
      Category = 'GarePGCCelere'
      Caption = 'Prima serie PGC Celere'
      Hint = 
        'Prima serie PGC Celere|Chiuso per 7" e poi aperto per 5" per 5 v' +
        'olte'
      OnExecute = actGarePrimaPGCCelereStartExecute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareProssimaPGCCelereStart: TAction
      Category = 'GarePGCCelere'
      Caption = 'Prossima serie PGC Celere'
      Hint = 
        'Prossima serie PGC Celere|Chiuso per 7" e poi aperto per 5" per ' +
        '5 volte'
      OnExecute = actGareProssimaPGCCelereStartExecute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actOpen: TAction
      Caption = 'Open'
      OnExecute = actOpenExecute
      OnUpdate = EnableIfConnectionIsClose
    end
    object actFnReadHoldingRegisters: TAction
      Category = 'Modbus'
      Caption = 'Read Holding Regs'
      OnExecute = actFnReadHoldingRegistersExecute
      OnUpdate = EnableIfConnectionIsOpen
    end
    object actFnReadInputRegisters: TAction
      Category = 'Modbus'
      Caption = 'Read Input Regs'
      OnExecute = actFnReadInputRegistersExecute
      OnUpdate = EnableIfConnectionIsOpen
    end
    object actGareProvaPA8: TAction
      Category = 'GarePistolaAutomatica'
      Caption = 'Serie di prova PA 8"'
      OnExecute = actGareProvaPA8Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGarePrimaPA6: TAction
      Category = 'GarePistolaAutomatica'
      Caption = 'Prima serie PA 6"'
      OnExecute = actGarePrimaPA6Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actFnPresetSingleRegister: TAction
      Category = 'Modbus'
      Caption = 'Preset Single Reg'
      OnExecute = actFnPresetSingleRegisterExecute
      OnUpdate = EnableIfConnectionIsOpen
    end
    object actFnPresetMultipleRegisters: TAction
      Category = 'Modbus'
      Caption = 'Preset Multiple Regs'
      OnExecute = actFnPresetMultipleRegistersExecute
      OnUpdate = EnableIfConnectionIsOpen
    end
    object actGarePrimaPA4: TAction
      Category = 'GarePistolaAutomatica'
      Caption = 'Prima serie PA 4"'
      OnExecute = actGarePrimaPA4Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actClose: TAction
      Caption = 'Close'
      OnExecute = actCloseExecute
      OnUpdate = EnableIfConnectionIsOpen
    end
    object actGarePrimaPGCMiratoStart: TAction
      Category = 'GarePGCMirato'
      Caption = 'Prima serie PGC Mirato'
      Hint = 'Prima serie PGC Mirato|Chiuso per 7" e poi aperto per 300"'
      OnExecute = actGarePrimaPGCMiratoStartExecute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareResetCycle: TAction
      Category = 'Gare'
      Caption = 'Reset'
      Hint = 'Reset sagome|Ciclo di reset delle sagome'
      OnExecute = actGareResetCycleExecute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareStop: TAction
      Category = 'Gare'
      Caption = 'Stop'
      OnExecute = actGareStopExecute
      OnUpdate = EnabledIfTrialIsRunning
    end
    object actGarePrimaPS10: TAction
      Category = 'GarePistolaStandard'
      Caption = 'Prima serie PS 10"'
      OnExecute = actGarePrimaPS10Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareProvaPGCCelereStart: TAction
      Category = 'GarePGCCelere'
      Caption = 'Serie di prova PGC Celere'
      Hint = 
        'Serie di prova PGC Celere|Chiuso per 7" e poi aperto per 5" per ' +
        '5 volte'
      OnExecute = actGareProvaPGCCelereStartExecute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareApertura: TAction
      Category = 'Gare'
      Caption = 'Apertura'
      Hint = 'Apertura|Apertura manuale sagome'
      OnExecute = actGareAperturaExecute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareChiusura: TAction
      Category = 'Gare'
      Caption = 'Chiusura'
      Hint = 'Chiusura|Chiusura manuale sagome'
      OnExecute = actGareChiusuraExecute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareEnb1_5: TAction
      Category = 'Gare'
      AutoCheck = True
      Caption = 'Abilitazione 1-5'
      Hint = 'Abilitazione sagome dalla 1 alla 5'
      OnExecute = actGareEnb1_5Execute
      OnUpdate = EnableIfConnectionIsOpen
    end
    object actGareEnb6_10: TAction
      Category = 'Gare'
      AutoCheck = True
      Caption = 'Abilitazione 6-10'
      Hint = 'Abilitazione sagome dalla 6 alla 10'
      OnExecute = actGareEnb6_10Execute
      OnUpdate = EnableIfConnectionIsOpen
    end
    object actGareProvaPS150: TAction
      Category = 'GarePistolaStandard'
      Caption = 'Serie di prova PS 150"'
      OnExecute = actGareProvaPS150Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGarePrimaPS20: TAction
      Category = 'GarePistolaStandard'
      Caption = 'Prima serie PS 20"'
      OnExecute = actGarePrimaPS20Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actWaveStartListening: TAction
      Category = 'Wave'
      Caption = 'Start listening'
      OnExecute = actWaveStartListeningExecute
      OnUpdate = actWaveStartListeningUpdate
    end
    object actWaveStopListening: TAction
      Category = 'Wave'
      Caption = 'Stop listening'
      OnExecute = actWaveStopListeningExecute
      OnUpdate = actWaveStopListeningUpdate
    end
    object actWaveSetParameters: TAction
      Category = 'Wave'
      Caption = 'Set parameters...'
      OnExecute = actWaveSetParametersExecute
      OnUpdate = actWaveSetParametersUpdate
    end
  end
  object ApplicationEvents1: TApplicationEvents
    OnIdle = ApplicationEvents1Idle
    Left = 480
    Top = 360
  end
  object tmrGare: TTimer
    Enabled = False
    Interval = 20
    OnTimer = tmrGareTimer
    Left = 292
    Top = 399
  end
  object tmrReadStatusPorta: TTimer
    Enabled = False
    OnTimer = tmrReadStatusPortaTimer
    Left = 364
    Top = 468
  end
end
