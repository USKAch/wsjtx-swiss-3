program test_packjt77_swiss_cantons

! WSJT-SWISS carries the Swiss canton in the ARRL Field Day message
! (type 0.3), with the 26 cantons in place of the ARRL sections. Every
! canton must survive pack and unpack, through both the standard and
! the multithreaded ("var") routines, and travel as its 1-based
! position in the canton list so WSJT-SWISS 2.7 and 3 decode each other.

  use packjt77
  implicit none

  character(len=3), parameter :: cantons(26) = [character(len=3) ::  &
       'AG','AI','AR','BE','BL','BS','FR','GE','GL','GR',          &
       'JU','LU','NE','NW','OW','SG','SH','SO','SZ','TG',          &
       'TI','UR','VD','VS','ZG','ZH']
  integer :: i, ntests

  ntests=0
  do i=1,size(cantons)
     call expect_round_trip('HB9BLA HB9XYZ 1A '//trim(cantons(i)), i)
     call expect_round_trip('HB9XYZ HB9BLA R 1A '//trim(cantons(i)), i)
  enddo
  call expect_not_field_day('WA9XYZ KA1ABC 1A EMA')

  write(*,1000) ntests
1000 format('packjt77 Swiss canton tests passed: ',i0)

contains

  subroutine expect_round_trip(message, index)
    character(len=*), intent(in) :: message
    integer, intent(in) :: index
    character(len=37) :: msg, got
    character(len=77) :: c77, c77var
    integer :: i3, n3, isec
    logical :: ok

    msg=message
    i3=-1
    n3=-1
    call pack77(msg,i3,n3,c77)
    if(i3.ne.0 .or. n3.ne.3) then
       write(*,1010) trim(message), i3, n3
1010   format('"',a,'" packed as type ',i0,'.',i0,', wanted 0.3')
       error stop 1
    endif
    read(c77(65:71),'(b7)') isec
    if(isec.ne.index) then
       write(*,1020) trim(message), isec, index
1020   format('"',a,'" sent canton index ',i0,', wanted ',i0)
       error stop 1
    endif
    call unpack77(c77,1,got,ok)
    if(.not.ok .or. got.ne.msg) then
       write(*,1030) trim(message), trim(got)
1030   format('"',a,'" unpacked as "',a,'"')
       error stop 1
    endif

    i3=-1
    n3=-1
    call pack77var(msg,i3,n3,c77var,0)
    if(c77var.ne.c77) then
       write(*,1040) trim(message)
1040   format('"',a,'" packs differently in pack77var')
       error stop 1
    endif
    call unpack77var(c77,1,got,ok,1)
    if(.not.ok .or. got.ne.msg) then
       write(*,1050) trim(message), trim(got)
1050   format('"',a,'" unpacked by unpack77var as "',a,'"')
       error stop 1
    endif
    ntests=ntests+1
  end subroutine expect_round_trip

  ! ARRL sections are no longer Field Day exchanges in WSJT-SWISS.
  subroutine expect_not_field_day(message)
    character(len=*), intent(in) :: message
    character(len=37) :: msg
    character(len=77) :: c77
    integer :: i3, n3

    msg=message
    i3=-1
    n3=-1
    call pack77(msg,i3,n3,c77)
    if(i3.eq.0 .and. (n3.eq.3 .or. n3.eq.4)) then
       write(*,1060) trim(message)
1060   format('"',a,'" still packs as an ARRL Field Day message')
       error stop 1
    endif
    ntests=ntests+1
  end subroutine expect_not_field_day

end program test_packjt77_swiss_cantons
